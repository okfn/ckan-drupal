import datetime
from sqlalchemy import types, Column, Table
from sqlalchemy.sql import select, and_, or_
from sqlalchemy import MetaData, create_engine
import json
import time
import urllib2
import urlparse

from ckan.plugins import IConfigurer, ISession, IActions
from ckan.plugins import implements, SingletonPlugin
import ckan.model as model
from ckan.logic.action import create, update, get
from ckan.controllers.api import ApiController
from ckan.logic import NotFound, NotAuthorized, ValidationError
from ckan import authz
from ckan.lib.navl.dictization_functions import DataError


class Drupal(SingletonPlugin):
    '''initial test of plugin'''
    implements(IConfigurer)
    implements(IActions)
    implements(ISession, inherit=True)

    def get_package_row(self, conn, package_id):
        return conn.execute(
            select(
                [self.package_table],
                self.package_table.c.id == package_id
            )
        ).fetchone()
            
    def update_drupal(self, session, conn):

        obj_cache = session._object_cache
        new = obj_cache['new']
        changed = obj_cache['changed']
        deleted = obj_cache['deleted']

        try:
            update_date = int(
                time.mktime(session.revision.timestamp.timetuple())
            )
        except AttributeError:
            update_date = int(time.time())

        package_rows = {}
        package_tags = {}

        inserts = []
        updates = []
        deletes = []

        for obj in new:
            if hasattr(obj, 'state') and 'pending' in obj.state:
                continue
            if hasattr(obj, 'current') and obj.current <> '1':
                continue
            if isinstance(obj, (model.Package, model.PackageRevision)):
                insert = self.add_insert(obj, self.package_table)
                package_rows[insert['id']] = insert
                inserts.append(insert)
            if isinstance(obj, (model.Resource, model.ResourceRevision)):
                inserts.append(self.add_insert(obj, self.resource_table))
            if isinstance(obj, (model.PackageExtra, model.PackageExtraRevision)):
                inserts.append(self.add_insert(obj, self.package_extra_table))
            if isinstance(obj, (model.PackageTag, model.PackageTagRevision)):
                inserts.append({'__table': self.tag_table, 'package_id': obj.package_id,
                                'name': obj.tag.name, 'id': obj.id})

        for obj in changed:
            if hasattr(obj, 'state') and 'pending' in obj.state:
                continue
            if hasattr(obj, 'current') and obj.current <> '1':
                continue
            if isinstance(obj, (model.Package, model.PackageRevision)):
                update = self.add_update(obj, self.package_table)
                package_row = package_rows.get(
                    obj.id,
                    self.get_package_row(conn, obj.id)
                )
                package_rows[update['id']] = update
                updates.append(update)
            if isinstance(obj, (model.Resource, model.ResourceRevision)):
                if obj.state == 'deleted':
                    deletes.append(self.add_delete(obj, self.resource_table, conn))
                else:
                    updates.append(self.add_update(obj, self.resource_table))
            if isinstance(obj, (model.PackageExtra, model.PackageExtraRevision)):
                if obj.state == 'deleted':
                    deletes.append(self.add_delete(obj, self.package_extra_table, conn))
                else:
                    updates.append(self.add_update(obj, self.package_extra_table))
            if isinstance(obj, (model.PackageTag, model.PackageTagRevision)):
                if obj.state == 'deleted':
                    deletes.append({'__table': self.tag_table, 'package_id': obj.package_id,
                                    'name': obj.tag.name, 'id': obj.id})
                else:
                    updates.append({'__table': self.tag_table, 'package_id': obj.package_id,
                                    'name': obj.tag.name, 'id': obj.id})


        for obj in deleted:
            if hasattr(obj, 'state') and 'pending' in obj.state:
                continue
            if hasattr(obj, 'current') and obj.current <> '1':
                continue
            if isinstance(obj, (model.Package, model.PackageRevision)):
                delete = self.add_delete(obj, self.package_table, conn)
                package_row = self.get_package_row(conn, obj.id)
                package_rows[delete['id']] = delete
                deletes.append(delete)
            if isinstance(obj, (model.PackageExtra, model.PackageExtraRevision)):
                deletes.append(self.add_delete(obj, self.package_extra_table, conn))
            if isinstance(obj, (model.Resource, model.ResourceRevision)):
                deletes.append(self.add_delete(obj, self.resource_table, conn))
            if isinstance(obj, (model.PackageTag, model.PackageTagRevision)):
                deletes.append({'__table': self.tag_table, 'package_id': obj.package_id,
                                'id': obj.id})

        for row in inserts + updates + deletes:
            if 'package_id' in row:
                package_id = row['package_id']
            else:
                package_id = row['id']
            if package_id in package_rows:
                package_rows[package_id]['update_date'] = update_date
            else:
                package_row = self.get_package_row(conn, package_id)
                update = {'__table': self.package_table, 
                          'id': package_id,
                          'update_date': update_date}
                updates.append(update)
                package_rows[package_id] = update

        for row in inserts:
           nid = session._context['nid']
           table = row.pop('__table') 
           row.update({'nid':nid})
           conn.execute(table.insert().values(**row))

        for row in updates:
           nid = session._context['nid']
           table = row.pop('__table') 
           id = row.pop('id')
           row.update({'nid':nid})
           conn.execute(table.update().where(table.c.id==id).values(**row))

        for row in deletes:
           table = row.pop('__table') 
           id = row.pop('id')
           conn.execute(table.delete().where(table.c.id==id))


    def add_insert(self, obj, table):

        insert = {'__table': table}
        for column in table.c:
            value = getattr(obj, column.name, None)
            if value is not None:
                insert[column.name] = value
        if isinstance(obj, model.Resource):
            insert['package_id'] = obj.resource_group.package_id
            insert['extras'] = json.dumps(insert['extras'])
        if isinstance(obj, model.ResourceRevision):
            insert['package_id'] = obj.coninuity.resource_group.package_id
            insert['extras'] = json.dumps(insert['extras'])
        return insert

    def add_update(self, obj, table):

        update = {'__table': table}
        for column in table.c:
            value = getattr(obj, column.name, None)
            if value is not None:
                update[column.name] = value
        if isinstance(obj, model.Resource):
            update['package_id'] = obj.resource_group.package_id
            update['extras'] = json.dumps(update['extras'])
        if isinstance(obj, model.ResourceRevision):
            update['package_id'] = obj.continuity.resource_group.package_id
            update['extras'] = json.dumps(update['extras'])
        return update

    def add_delete(self, obj, table, conn):

        delete = {'__table': table}
        for column in table.c:
            value = getattr(obj, column.name, None)
            if value is not None:
                delete[column.name] = value
        if isinstance(obj, (model.Resource, model.ResourceRevision)):
            package_id = conn.execute(
                select(
                    [self.resource_table],
                    self.resource_table.c.id == obj.id
                )
            ).fetchone()["package_id"]
            delete["package_id"] = package_id
        return delete

    def before_commit(self, session):
        session.flush()
        if not hasattr(session, '_object_cache'):
            return
        conn = self.engine.connect()
        trans = conn.begin()
        try:
            self.update_drupal(session, conn)
            trans.commit()
        except:
            trans.rollback()
            session.rollback()
            raise
        finally:
            conn.close()

    def drupal_package_create(self, context, data_dict):

        session = context['model'].Session
        context['nid'] = data_dict.pop('nid')
        package_create = create.package_create(context, data_dict)
        package_create['nid'] = context['nid']
        package_create['revision_message'] = '%s-%s'%(session.revision.id,session.revision.message)
        return package_create

    def drupal_package_update(self, context, data_dict):
        session = context['model'].Session
        context['nid'] = data_dict.pop('nid')
        package_update = update.package_update(context, data_dict)
        package_update['nid'] = context['nid']
        package_update['revision_message'] = '%s-%s'%(session.revision.id,session.revision.message)
        return package_update

    def package_create(self, context, data_dict):

        preview = context.get('preview', False)
        if preview:
            return
        session = context['model'].Session
        url = urlparse.urljoin(self.base_url, 'services/package.json')
        data_dict['body'] = data_dict.get('notes', '')
        data = json.dumps({'data': data_dict})
        req = urllib2.Request(url, data, {'Content-type': 'application/json'})
        ##XXX think about error conditions a bit more
        f = urllib2.urlopen(req, None, 3)
        try:
            drupal_info = json.loads(f.read())
        finally:
            f.close()
        nid = drupal_info['nid']
        context['nid'] = nid
        try:
            package_create = create.package_create(context, data_dict)
        except:
            url = urlparse.urljoin(self.base_url, 'services/package/%s.json' % (nid))
            req = urllib2.Request(url)
            req.get_method = lambda: 'DELETE'
            f = urllib2.urlopen(req, None, 3)
            try:
                drupal_info = f.read()
            finally:
                f.close()
            raise

        package_create['nid'] = context['nid']
        package_create['revision_message'] = '%s-%s'%(session.revision.id,session.revision.message)
        return package_create

    def package_update(self, context, data_dict):
        preview = context.get('preview', False)
        if preview:
            return
        if 'id' not in data_dict:
            raise NotFound
        result = self.engine.execute(
                select(
                    [self.package_table.c.nid],
                    or_(self.package_table.c.id == data_dict['id'],
                        self.package_table.c.name == data_dict['id'])
                )
        ).fetchone()
        if not result:
            raise NotFound
        nid = result['nid']
        data_dict['body'] = data_dict['notes']

        url = urlparse.urljoin(self.base_url, 'services/package/%s.json' % (nid))
        data = json.dumps({'data': data_dict})
        req = urllib2.Request(url, data, {'Content-type': 'application/json'})
        req.get_method = lambda: 'PUT'
        ##XXX think about error conditions a bit more
        f = urllib2.urlopen(req, None, 3)
        try:
            drupal_info = json.loads(f.read())
        finally:
            f.close()

        session = context['model'].Session
        context['nid'] = result['nid']
        package_update = update.package_update(context, data_dict)
        package_update['nid'] = result['nid']
        package_update['revision_message'] = '%s-%s'%(session.revision.id,session.revision.message)
        return package_update

    def package_purge(self, context, data_dict):
        if not authz.Authorizer().is_sysadmin(unicode(context['user'])):
            raise NotAuthorized
        if 'id' not in data_dict:
            raise NotFound
        package = context['model'].Package.get(data_dict['id'])
        package.purge()
        package = context['model'].Session.flush()
        result = self.engine.execute(
                select(
                    [self.package_table.c.nid],
                    or_(self.package_table.c.id == data_dict['id'],
                        self.package_table.c.name == data_dict['id'])
                )
        ).fetchone()
        if not result:
            raise NotFound

        nid = result['nid']
        url = urlparse.urljoin(self.base_url, 'services/package/%s.json' % (nid))
        req = urllib2.Request(url)
        req.get_method = lambda: 'DELETE'
        f = urllib2.urlopen(req, None, 3)
        try:
            drupal_info = f.read()
        finally:
            f.close()

        
        package = context['model'].Session.commit()

    def get_actions(self):
        return {'drupal_package_create': self.drupal_package_create,
                'drupal_package_update': self.drupal_package_update,
                'package_purge': self.package_purge,
                'package_create': self.package_create,
                'package_update': self.package_update,
                'migrate_data': self.migrate_data}

    def populate_licences(self):
        licences = get.licence_list({'model':model}, {})
        conn = self.engine.connect()
        trans = conn.begin()
        try:
            conn.execute(self.license_table.delete())
            inserts = []
            for licence in licences:
                inserts.append(
                    {'license_id': licence['id'],
                     'license_name': licence['title'],
                     'is_osi_compliant': licence.get(
                         'is_osi_compliant',
                          False
                     ),
                     'is_okd_compliant': licence.get(
                          'is_okd_compliant',
                          False)
                     }
                )
            conn.execute(self.license_table.insert(), inserts)
            trans.commit()
        except:
            trans.rollback()
            raise
        finally:
            conn.close()

    def update_config(self, config):
        config['ckan.site_title'] = 'CKAN-Drupal'

        url = config['drupal.db_url'] 
        self.base_url = config['drupal.base_url'] 

        self.engine = create_engine(url)
        self.metadata = MetaData(self.engine)

        PACKAGE_NAME_MAX_LENGTH = 100
        PACKAGE_VERSION_MAX_LENGTH = 100

        self.package_table = Table('ckan_package', self.metadata,
            Column('nid', types.Integer, unique=True),
            Column('id', types.Unicode(100), primary_key=True),
            Column('name', types.Unicode(PACKAGE_NAME_MAX_LENGTH),
                   nullable=False, unique=True),
            Column('title', types.UnicodeText),
            Column('author', types.UnicodeText),
            Column('author_email', types.UnicodeText),
            Column('maintainer', types.UnicodeText),
            Column('maintainer_email', types.UnicodeText),                      
            Column('notes', types.UnicodeText),
            Column('license_id', types.UnicodeText),
            Column('update_date', types.Integer),
            Column('state', types.UnicodeText),
            Column('completed', types.Boolean),
        )

        self.resource_table = Table(
            'ckan_resource', self.metadata,
            Column('nid', types.Integer),
            ## cache of package id to make things easier
            Column('package_id', types.UnicodeText),
            ##
            Column('id', types.Unicode(100), primary_key=True),
            Column('resource_group_id', types.UnicodeText),
            Column('package_id', types.UnicodeText),
            Column('url', types.UnicodeText, nullable=False),
            Column('format', types.UnicodeText),
            Column('description', types.UnicodeText),
            Column('hash', types.UnicodeText),
            Column('position', types.Integer),
            Column('extras', types.UnicodeText),
            )

        self.package_extra_table = Table('ckan_package_extra', self.metadata,
            Column('nid', types.Integer),
            Column('id', types.Unicode(100), primary_key=True),
            Column('package_id', types.UnicodeText),
            Column('key', types.UnicodeText),
            Column('value', types.UnicodeText),
        )

        self.tag_table = Table('ckan_tag', self.metadata,
            Column('nid', types.UnicodeText),
            Column('id', types.Unicode(100), primary_key=True),
            Column('package_id', types.UnicodeText),
            Column('name', types.UnicodeText),
        )

        self.license_table = Table('ckan_license', self.metadata,
            Column('license_id', types.UnicodeText),
            Column('license_name', types.UnicodeText),
            Column('is_okd_compliant', types.Boolean),
            Column('is_osi_compliant', types.Boolean),
        )

        self.metadata.create_all(self.engine)

        self.populate_licences()

    def migrate_data(self, context, data_dict):
        if not authz.Authorizer().is_sysadmin(unicode(context['user'])):
            raise NotAuthorized
        model.Session.remove()
        model.Session().connection
        conn_ckan = model.Session.connection()
        conn_drupal = self.engine.connect()

        #package
        packages = conn_ckan.execute(
            select(
                [model.package_revision_table],
                and_(model.package_revision_table.c.current == True,
                     model.package_revision_table.c.state.in_(['active','deleted']))
            )
        ).fetchall()
        package_inserts = []
        for package in packages:
            insert = {}
            for column in self.package_table.c:
                if column in package:
                    insert[column.name] = package[column.name]
            package_inserts.append(insert)
        conn_drupal.execute(self.package_table.insert(), package_inserts)
        print 'packages done'
        
        #resources
        resources = conn_ckan.execute(
            select(
                [model.resource_revision_table, model.resource_group_table.c.package_id],
                 and_(model.resource_revision_table.c.current == True,
                 model.resource_revision_table.c.state.in_(['active','deleted']),
                 model.resource_group_table.c.id == model.resource_revision_table.c.resource_group_id,
                )
            )
        ).fetchall()

        resource_inserts = []
        for resource in resources:
            insert = {}
            for column in self.resource_table.c:
                if column in resource:
                    insert[column.name] = resource[column.name]
            insert['extras'] = json.dumps(insert['extras'])
            resource_inserts.append(insert)
        conn_drupal.execute(self.resource_table.insert(), resource_inserts)
        print 'resources done'
        
        #extras
        extras = conn_ckan.execute(
            select(
                [model.extra_revision_table],
                and_(model.extra_revision_table.c.current == True,
                     model.extra_revision_table.c.state.in_(['active','deleted']))
            )
        ).fetchall()
        package_extra_inserts = []
        for extra in extras:
            insert = {}
            for column in self.package_extra_table.c:
                if column in extra:
                    insert[column.name] = extra[column.name]
            insert['value'] = json.dumps(insert['value'])
            package_extra_inserts.append(insert)
        conn_drupal.execute(self.package_extra_table.insert(), package_extra_inserts)
        print 'extras done'

        #tags
        tags = conn_ckan.execute(
            select(
                [model.package_tag_revision_table, model.tag_table.c.name],
                and_(model.package_tag_revision_table.c.current == True,
                     model.package_tag_revision_table.c.state.in_(['active','deleted']),
                     model.tag_table.c.id == model.package_tag_revision_table.c.tag_id)
            )
        ).fetchall()
        tag_inserts = []
        for tag in tags:
            tag_inserts.append({'name': tag['name'],
                                'id': tag['id'],
                                'package_id': tag['package_id']})
        conn_drupal.execute(self.tag_table.insert(), tag_inserts)
        print 'tags done'

        ## get nodes

        packages = conn_drupal.execute(
            select(
                [self.package_table],
            )
        ).fetchall()

        for num, package in enumerate(packages):
            print num
            data_dict = {}
            for column in self.package_table.c:
                data_dict[column.name] = package[column.name]
            url = urlparse.urljoin(self.base_url, 'services/package.json')
            data_dict['body'] = data_dict.get('notes', '')
            if not data_dict['title']:
                data_dict['title'] = data_dict['name']
            tags = conn_drupal.execute(
                select(
                    [self.tag_table.c.name],
                    self.tag_table.c.package_id == package['id']
                )
            ).fetchall()
            data_dict['tags'] = [{'name': tag[0]} for tag in tags]
            data = json.dumps({'data': data_dict})
            req = urllib2.Request(url, data, {'Content-type': 'application/json'})
            f = urllib2.urlopen(req, None, 3)
            try:
                drupal_info = json.loads(f.read())
            finally:
                f.close()
            nid = drupal_info['nid']
            update = {'nid': nid}

            conn_drupal.execute(
                self.package_table.update().where(
                    self.package_table.c.id==data_dict['id']
                ).values(
                    nid=nid
                )
            )
            
        conn_drupal.execute('update ckan_resource set nid = (select nid from ckan_package where ckan_resource.package_id = ckan_package.id);')
        conn_drupal.execute('update ckan_package_extra set nid = (select nid from ckan_package where ckan_package_extra.package_id = ckan_package.id);')
        conn_drupal.execute('update ckan_tag set nid = (select nid from ckan_package where ckan_tag.package_id = ckan_package.id);')
        print 'finished migration'


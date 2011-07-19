from ckan.lib.create_test_data import CreateTestData
import ckan.model as model
from ckan.tests import WsgiAppCase
import json
from ckan import plugins
from pprint import pprint, pformat
from pylons import config
from sqlalchemy import MetaData, create_engine, Table

class TestAction(WsgiAppCase):

    @classmethod
    def setup_class(cls):
        model.repo.rebuild_db()
        CreateTestData.create()
        plugins.load('drupal')
        from ckan.plugins import PluginImplementations
        from ckan.plugins.interfaces import IConfigurer
        for plugin in PluginImplementations(IConfigurer):
            plugin.update_config(config)

        url = config['drupal.db_url'] 
        cls.engine = create_engine(url, echo=True)
        cls.metadata = MetaData(cls.engine)
        cls.package_table = Table('ckan_package',
                                  cls.metadata,
                                  autoload = True)
        cls.extra_table = Table('ckan_package_extra',
                                  cls.metadata,
                                  autoload = True)
        cls.resource_table = Table('ckan_package_extra',
                                  cls.metadata,
                                  autoload = True)


    def test_01_create_update_package(self):

        package = {
            'nid': 1,
            'author': None,
            'author_email': None,
            'extras': [{'key': u'original media','value': u'"book"'}],
            'license_id': u'other-open',
            'maintainer': None,
            'maintainer_email': None,
            'name': u'moo1',
            'notes': u'Some test now',
            'resources': [{'alt_url': u'alt123',
                           'description': u'Full text.',
                           'extras': {u'alt_url': u'alt123', u'size': u'123'},
                           'format': u'plain text',
                           'hash': u'abc123',
                           'position': 0,
                           'url': u'http://www.annakarenina.com/download/'},
                          {'alt_url': u'alt345',
                           'description': u'Index of the novel',
                           'extras': {u'alt_url': u'alt345', u'size': u'345'},
                           'format': u'json',
                           'hash': u'def456',
                           'position': 1,
                           'url': u'http://www.annakarenina.com/index.json'}],
            'tags': [{'name': u'russian'}, {'name': u'tolstoy'}],
            'title': u'A Novel By Tolstoy',
            'url': u'http://www.annakarenina.com',
            'version': u'0.7a'
        }

        wee = json.dumps(package)
        postparams = '%s=1' % json.dumps(package)
        res = self.app.post('/api/action/drupal_package_create', params=postparams,
                            extra_environ={'Authorization': 'tester'})
        package_created = json.loads(res.body)['result']


        package_created['name'] = 'moo2'
        postparams = '%s=1' % json.dumps(package_created)
        res = self.app.post('/api/action/drupal_package_update', params=postparams,
                            extra_environ={'Authorization': 'tester'})

        package_updated = json.loads(res.body)['result']
        package_updated.pop('revision_id')
        package_updated.pop('revision_timestamp')
        package_updated.pop('revision_message')
        package_created.pop('revision_id')
        package_created.pop('revision_timestamp')
        package_created.pop('revision_message')
        pprint(package_updated)
        pprint(package_created)
        assert package_updated == package_created#, (pformat(json.loads(res.body)), pformat(package_created['result']))


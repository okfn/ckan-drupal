import re
from pylons.i18n import _, ungettext, N_, gettext
from ckan.lib.navl.dictization_functions import Invalid, missing, unflatten
from ckan.authz import Authorizer

def package_id_not_changed(value, context):

    package = context.get('package')
    if package and value != package.id:
        raise Invalid(_('Cannot change value of key from %s to %s. '
                        'This key is read-only') % (package.id, value))
    return value

def no_http(value, context):

    model = context['model']
    session = context['session']

    if 'http:' in value:
        raise Invalid(_('No links are allowed in the log_message.'))
    return value

def package_id_exists(value, context):

    model = context['model']
    session = context['session']

    result = session.query(model.Package).get(value)
    if not result:
        raise Invalid(_('Package was not found.'))
    return value

def package_name_exists(value, context):

    model = context['model']
    session = context['session']

    result = session.query(model.Package).filter_by(name=value).first()

    if not result:
        raise Invalid(_('Package with name %r does not exist.') % str(value))
    return value

def package_id_or_name_exists(value, context):

    model = context['model']
    session = context['session']

    result = session.query(model.Package).get(value)
    if result:
        return value

    result = session.query(model.Package).filter_by(name=value).first()

    if not result:
        raise Invalid(_('Package was not found.'))

    return result.id

def extras_unicode_convert(extras, context):
    for extra in extras:
        extras[extra] = unicode(extras[extra])
    return extras

name_match = re.compile('[a-z0-9_\-]*$')
def name_validator(val, context):
    # check basic textual rules
    if len(val) < 2:
        raise Invalid(_('Name must be at least %s characters long') % 2)
    if not name_match.match(val):
        raise Invalid(_('Name must be purely lowercase alphanumeric '
                        '(ascii) characters and these symbols: -_'))
    return val

def package_name_validator(key, data, errors, context):
    model = context["model"]
    session = context["session"]
    package = context.get("package")

    query = session.query(model.Package.name).filter_by(name=data[key])
    if package:
        package_id = package.id
    else:
        package_id = data.get(key[:-1] + ("id",))
    if package_id and package_id is not missing:
        query = query.filter(model.Package.id <> package_id) 
    result = query.first()
    if result:
        errors[key].append(_('Package name already exists in database'))

def duplicate_extras_key(key, data, errors, context):

    unflattened = unflatten(data)
    extras = unflattened.get('extras', [])
    extras_keys = []
    for extra in extras:
        if not extra.get('deleted'):
            extras_keys.append(extra['key'])
    
    for extra_key in set(extras_keys):
        extras_keys.remove(extra_key)
    if extras_keys:
        errors[key].append(_('Duplicate key "%s"') % extras_keys[0])
    
def group_name_validator(key, data, errors, context):
    model = context['model']
    session = context['session']
    group = context.get('group')

    query = session.query(model.Group.name).filter_by(name=data[key])
    if group:
        group_id = group.id
    else:
        group_id = data.get(key[:-1] + ('id',))
    if group_id and group_id is not missing:
        query = query.filter(model.Group.id <> group_id) 
    result = query.first()
    if result:
        errors[key].append(_('Group name already exists in database'))

def tag_length_validator(value, context):

    if len(value) < 2:
        raise Invalid(
            _('Tag "%s" length is less than minimum %s') % (value, 2)
        )
    return value

def tag_name_validator(value, context):

    tagname_match = re.compile('[\w\-_.]*$', re.UNICODE)
    if not tagname_match.match(value):
        raise Invalid(_('Tag "%s" must be alphanumeric '
                        'characters or symbols: -_.') % (value))
    return value

def tag_not_uppercase(value, context):

    tagname_uppercase = re.compile('[A-Z]')
    if tagname_uppercase.search(value):
        raise Invalid(_('Tag "%s" must not be uppercase' % (value)))
    return value

def tag_string_convert(key, data, errors, context):

    value = data[key]

    tags = value.split()
    for num, tag in enumerate(tags):
        data[('tags', num, 'name')] = tag.lower()

    for tag in tags:
        tag_length_validator(tag, context)
        tag_name_validator(tag, context)

def ignore_not_admin(key, data, errors, context):

    model = context['model']
    user = context.get('user')

    if user and Authorizer.is_sysadmin(user):
        return

    pkg = context.get('package')
    if (user and pkg and 
        Authorizer().is_authorized(user, model.Action.CHANGE_STATE, pkg)):
        return

    data.pop(key)


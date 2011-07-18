<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function features_ckan_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_package_access
  $groups['ckan_publisher-group_package_access'] = array(
    'group_type' => 'standard',
    'type_name' => 'ckan_publisher',
    'group_name' => 'group_package_access',
    'label' => 'Package access',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '9',
    'fields' => array(
      '0' => 'field_maintainers',
      '1' => 'field_managers',
    ),
  );

  // Exported group: group_publisher_information
  $groups['ckan_publisher-group_publisher_information'] = array(
    'group_type' => 'standard',
    'type_name' => 'ckan_publisher',
    'group_name' => 'group_publisher_information',
    'label' => 'Publisher information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '2',
    'fields' => array(
      '0' => 'field_shortname',
      '1' => 'field_website',
      '2' => 'field_logo',
      '3' => 'field_public_email',
      '4' => 'field_feedback_email',
      '5' => 'field_parent_publisher',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Package access');
  t('Publisher information');

  return $groups;
}

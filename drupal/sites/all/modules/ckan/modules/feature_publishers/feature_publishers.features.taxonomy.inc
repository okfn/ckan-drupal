<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function feature_publishers_taxonomy_default_vocabularies() {
  return array(
    'publishers' => array(
      'name' => 'Publishers',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '1',
      'multiple' => '1',
      'required' => '0',
      'tags' => '0',
      'module' => 'features_publishers',
      'weight' => '0',
      'nodes' => array(
        'ckan_package' => 'ckan_package',
      ),
    ),
  );
}

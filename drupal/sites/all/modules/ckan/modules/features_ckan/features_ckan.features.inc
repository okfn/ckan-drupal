<?php

/**
 * Implementation of hook_node_info().
 */
function features_ckan_node_info() {
  $items = array(
    'ckan_package' => array(
      'name' => t('Package'),
      'module' => 'features',
      'description' => t('A ckan package representation'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'ckan_publisher' => array(
      'name' => t('Publisher'),
      'module' => 'features',
      'description' => t('A publisher of a package'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

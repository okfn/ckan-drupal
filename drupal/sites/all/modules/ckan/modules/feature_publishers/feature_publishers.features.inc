<?php

/**
 * Implementation of hook_node_info().
 */
function feature_publishers_node_info() {
  $items = array(
    'ckan_publisher' => array(
      'name' => t('Publisher'),
      'module' => 'features',
      'description' => '',
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

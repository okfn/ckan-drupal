<?php

/**
	--
	-- Table structure for table `ckan_package`
	--

	CREATE TABLE `ckan_package` (
	  `nid` int(11) DEFAULT NULL,
	  `id` varchar(100) NOT NULL,
	  `name` varchar(100) NOT NULL,
	  `title` text,
	  `version` varchar(100) DEFAULT NULL,
	  `url` text,
	  `author` text,
	  `author_email` text,
	  `maintainer` text,
	  `maintainer_email` text,
	  `notes` text,
	  `license_id` text,
	  `update_date` datetime DEFAULT NULL,
	  PRIMARY KEY (`id`),
	  UNIQUE KEY `name` (`name`),
	  UNIQUE KEY `nid` (`nid`)
	)
*/


function ckan_views_data()  {
  // Basic table information for ckan_package.

	//  The group will appear in the UI in the dropdown tha allows you
  //  to narrow down which fields and filters are available.
  $data = array();
  $data['ckan_package']['table']['group']  = t('CKAN');

  // Let Views know that our ckan_package table joins to the 'node'
  // base table. This means it will be available when listing
  // nodes and automatically make its fields appear.
  //
  $data['ckan_package']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  // CKAN package id
  $data['ckan_package']['id'] = array(
    'title' => t('Package id'),
    'help' => t('The package id from CKAN.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['name'] = array(
    'title' => t('Package name'),
    'help' => t('A unique identifier for the package.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['title'] = array(
    'title' => t('Package title'),
    'help' => t('A short descriptive title for the data set.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_package']['version'] = array(
    'title' => t('Version'),
    'help' => t('A number representing the version.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_package']['url'] = array(
    'title' => t('URL'),
    'help' => t('The URL for the web page describing the data (not the data itself).'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['author'] = array(
    'title' => t('Author'),
    'help' => t('The name of the main contact for the package.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['author_email'] = array(
    'title' => t('Author\'s email'),
    'help' => t('Email address for enquiries about this particular dataset.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['maintainer'] = array(
    'title' => t('Maintainer'),
    'help' => t('Another important contact person who is not the author.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['maintainer_email'] = array(
    'title' => t('Maintainer\'s email'),
    'help' => t('Email address for the maintainer.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['Notes'] = array(
    'title' => t('notes'),
    'help' => t('The main description of the dataset.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );



  $data['ckan_package']['maintainer_email'] = array(
    'title' => t('Maintainer\'s email'),
    'help' => t('The maintainer\'s email.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


  $data['ckan_package']['license_id'] = array(
    'title' => t('License'),
    'help' => t('The licence under which the dataset is released..'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_package']['update_date'] = array(
    'title' => t('Package updated date'),
    'help' => t('The date the package was last updated in CKAN (not the drupal node).'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
	  ),
  );

  $data['ckan_package']['state'] = array(
    'title' => t('State'),
    'help' => t('The package state from ckan).'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_package']['completed'] = array(
    'title' => t('Completed'),
    'help' => t('The transaction state from ckan.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );


   // Basic table information for ckan_resource.

	//  The group will appear in the UI in the dropdown tha allows you
  //  to narrow down which fields and filters are available.
  $data['ckan_resource']['table']['group']  = t('CKAN');

  // Let Views know that our ckan_package table joins to the 'node'
  // base table. This means it will be available when listing
  // nodes and automatically make its fields appear.
  //
  // @todo Check if we can do a better join than just nid for resources
  $data['ckan_resource']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    )
  );

  $data['ckan_resource']['id'] = array(
    'title' => t('Resource id'),
    'help' => t('The resource id.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['resource_group_id'] = array(
    'title' => t('Resource group id'),
    'help' => t('The resource_group_id.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['url'] = array(
    'title' => t('Resource url'),
    'help' => t('The resource url.'),
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['format'] = array(
    'title' => t('Resource format'),
    'help' => t('The resource format.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['description'] = array(
    'title' => t('Resource description'),
    'help' => t('The resource description.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['hash'] = array(
    'title' => t('Resource hash'),
    'help' => t('The resource hash.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  $data['ckan_resource']['position'] = array(
    'title' => t('Resource position'),
    'help' => t('The resource position.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
	  ),
  );

  return $data;
}



	/**
	 * Default Views
	 *
	 */
function ckan_views_default_views() {

  /*
	 * Package report	view
	 */
  $view = new view;
  $view->name = 'ckan_packages';
  $view->description = 'List of all CKAN packages';
  $view->tag = 'CKAN';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 3.0-alpha1;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'license_id' => 'license_id',
    'update_date' => 'update_date',
    'url' => 'url',
    'author' => 'author',
    'version' => 'version',
    'Notes' => 'Notes',
    'url_1' => 'url_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'license_id' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'update_date' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'url' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'author' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'version' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'Notes' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'url_1' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: Node: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: CKAN: Package title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  /* Field: CKAN: License */
  $handler->display->display_options['fields']['license_id']['id'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['license_id']['field'] = 'license_id';
  $handler->display->display_options['fields']['license_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['license_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['license_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['license_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['license_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['license_id']['empty_zero'] = 0;
  /* Field: CKAN: Package updated date */
  $handler->display->display_options['fields']['update_date']['id'] = 'update_date';
  $handler->display->display_options['fields']['update_date']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['update_date']['field'] = 'update_date';
  $handler->display->display_options['fields']['update_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['update_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['update_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['update_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['update_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['update_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['update_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['update_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['update_date']['empty_zero'] = 0;
  /* Field: CKAN: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['url']['empty_zero'] = 0;
  $handler->display->display_options['fields']['url']['display_as_link'] = 1;
  /* Field: CKAN: Author */
  $handler->display->display_options['fields']['author']['id'] = 'author';
  $handler->display->display_options['fields']['author']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['author']['field'] = 'author';
  $handler->display->display_options['fields']['author']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['author']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['author']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['author']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['author']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['author']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['author']['alter']['html'] = 0;
  $handler->display->display_options['fields']['author']['hide_empty'] = 0;
  $handler->display->display_options['fields']['author']['empty_zero'] = 0;
  /* Field: CKAN: Version */
  $handler->display->display_options['fields']['version']['id'] = 'version';
  $handler->display->display_options['fields']['version']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['version']['field'] = 'version';
  $handler->display->display_options['fields']['version']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['version']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['version']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['version']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['version']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['version']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['version']['alter']['html'] = 0;
  $handler->display->display_options['fields']['version']['hide_empty'] = 0;
  $handler->display->display_options['fields']['version']['empty_zero'] = 0;
  /* Field: CKAN: notes */
  $handler->display->display_options['fields']['Notes']['id'] = 'Notes';
  $handler->display->display_options['fields']['Notes']['table'] = 'ckan_package';
  $handler->display->display_options['fields']['Notes']['field'] = 'Notes';
  $handler->display->display_options['fields']['Notes']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['Notes']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['Notes']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['Notes']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['Notes']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['Notes']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['Notes']['alter']['html'] = 0;
  $handler->display->display_options['fields']['Notes']['hide_empty'] = 0;
  $handler->display->display_options['fields']['Notes']['empty_zero'] = 0;
  /* Field: CKAN: Resource url */
  $handler->display->display_options['fields']['url_1']['id'] = 'url_1';
  $handler->display->display_options['fields']['url_1']['table'] = 'ckan_resource';
  $handler->display->display_options['fields']['url_1']['field'] = 'url';
  $handler->display->display_options['fields']['url_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['url_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['url_1']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['url_1']['alter']['path'] = 'reports/packages/[nid]';
  $handler->display->display_options['fields']['url_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['url_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['url_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['url_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['url_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['url_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['url_1']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'reports/packages';


  //add View
	$views[$view->name] = $view;


	/*
	 * Resource report	view
	 */
  $view = new view;
  $view->name = 'ckan_resources';
  $view->description = 'View resources for a package';
  $view->tag = 'CKAN';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 3.0-alpha1;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'description' => 'description',
    'position' => 'position',
    'url' => 'url',
    'nid' => 'nid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'description' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'position' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'url' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
    'nid' => array(
      'sortable' => 1,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: Node: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: CKAN: Resource description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'ckan_resource';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['description']['empty_zero'] = 0;
  /* Field: CKAN: Resource url */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'ckan_resource';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['url']['empty_zero'] = 0;
  /* Field: CKAN: Resource position */
  $handler->display->display_options['fields']['position']['id'] = 'position';
  $handler->display->display_options['fields']['position']['table'] = 'ckan_resource';
  $handler->display->display_options['fields']['position']['field'] = 'position';
  $handler->display->display_options['fields']['position']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['position']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['position']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['position']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['position']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['position']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['position']['alter']['html'] = 0;
  $handler->display->display_options['fields']['position']['hide_empty'] = 0;
  $handler->display->display_options['fields']['position']['empty_zero'] = 0;
  /* Argument: Node: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'reports/packages/%';



	//add View
	$views[$view->name] = $view;


	return $views;
}


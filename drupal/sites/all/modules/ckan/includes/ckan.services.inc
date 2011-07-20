<?php

 /**
  * Implementation of hook_default_services_endpoint().
  */
  function ckan_default_services_endpoint() {

  $endpoints = array();

  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'ckan';
  $endpoint->title = 'packages';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'services';
  $endpoint->authentication = array();
  $endpoint->resources = array(
    'package' => array(
      'operations' => array(
        'index' => array(
          'enabled' => 1,
        ),
        'retrieve' => array(
          'enabled' => 1,
        ),
        'create' => array(
          'enabled' => 1,
        ),
        'update' => array(
          'enabled' => 1,
        ),
        'delete' => array(
          'enabled' => 1,
        ),
      ),
      'actions' => array(
        'save' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 0;



	$endpoints[] = $endpoint;

  return $endpoints;
  }
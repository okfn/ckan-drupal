<?php
 /*
  * @file ckanresources.inc
  *
  * Callbacks for CKAN packages
  *
  *
  *
  */


  /**
  *  Function for index
  *
  *  @return object
  *  The results to render
  */
function  _ckanrest_index() {
  $results = array();
  $query = "SELECT nid, title from {node}
            WHERE type = 'ckan_package'";
  $resource = db_query($query);
  while ($row = db_fetch_array($resource)) $results[] = $row;
  return $results;
}


/**
  *  Function for retrive
  *  @param nid
  *  The package nid used to retreive the data
  *  @return object
  *  The result to render
  */
function  _ckanrest_retrieve($nid) {
  $result = array();
  $query = "SELECT * from {node}
            WHERE type = 'ckan_package'
            AND nid = %d LIMIT 0,1";
  $resource = db_query($query, $nid);
  $result = db_fetch_array($resource);
  return $result;
}


 /**
  *  Function for create
  *
  *
  */
function  _ckanrest_create($data) {

  if (!array_key_exists('title', $data)) { return services_error("Not Acceptable. 'title' key missing.", 406);}
  if (empty($data['title'])) { return services_error("Not Acceptable. 'title' can not be empty.", 406);}

  $response = array();
  $pnode = new stdClass();
  $pnode->type = 'ckan_package';
  $pnode->title = $data['title'];
  $pnode->body =  $data['body'];
  $pnode->uid = 1;
  $pnode->name = "admin";
  $pnode->status = $data['status'];
  $pnode->services_call = TRUE;

  //Add Tags
  if ((array_key_exists('terms', $data))) {
    $pnode->taxonomy = null;   //Clear all existing terms if key is given
    $ckan_vocabulary_id = variable_get('ckan_vocabulary_id', '');
    $terms = implode(',', $data['terms']);
    $pnode->taxonomy['tags'][$ckan_vocabulary_id] = $terms;
  }


  node_save($pnode);

  //Check the node has been saved
  if (is_numeric($pnode->nid)) {
    $response = $pnode;
  } else {
    // You shouldn't get here.
    return services_error('Node has no nid.', 406);
  }

return $response;
}


 /**
  *  Function for Delete
  *
  */
function  _ckanrest_delete($nid) {

  $response = array();

  $query = "SELECT * from {node}
            WHERE nid = %d LIMIT 0,1";
  $resource = db_query($query, $nid);
  $result = db_fetch_array($resource);

  if (!$result['nid']) { return services_error('Can not find node', 406); }

  if ($result['type'] == 'ckan_package') {
    //@todo Unsafe user switching. Either change code or complete API authorisation work.
    global $user;
    $original_user = $user;
    $user = user_load(1);
    node_delete($nid);
    $user = $original_user;

    return array('deleted'=>$nid);
  } else {
    return services_error('Not a package node.', 406);
  }

}


 /**
  *  Function for action, update
  *
  *  Update/save the node. Details in the ckan_package table will be changed by ckan.
  *
  */
function  _ckanrest_update($nid, $data) {
  $node = node_load($nid);
  $node->services_call = TRUE;

  $ckan_vocabulary_id = variable_get('ckan_vocabulary_id', '');
  if (!is_numeric($ckan_vocabulary_id)) {
      return services_error('No CKAN vocabulary ID set in admin/settings/ckan.', 406);
  }

  // Check the node exists.
  if (!$node->nid) {return services_error('Not a node.', 404);}

  // Check the node is the correct type.
  if (!$node->type == 'ckan_package') {return services_error('Not a package node.', 406);}

  // Update title, body
  $node->title = $data['title'] ?  $data['title']: $node->title ;
  $node->body = $data['body'] ?  $data['body'] : $node->body ;
  $node->status = $data['status'];

  //Add Tags
  if ((array_key_exists('terms', $data))) {
    $node->taxonomy = null;   //Clear all existing terms if key is given
    $ckan_vocabulary_id = variable_get('ckan_vocabulary_id', '');
    $terms = implode(',', $data['terms']);
    $node->taxonomy['tags'][$ckan_vocabulary_id] = $terms;
  }

  node_save($node);
  return $node;
}

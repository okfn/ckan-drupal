<?php
 /*
  * @file ckanresources.inc
  *
  * Callbacks for CKAN packages
  *
  *
  *
  */

/****************************************************************
  Examples of usage

  Index     GET   {site}{basepath}/services/package.json

  Retrieve  GET   {site}{basepath}/services/package/{nid}.json

  Create    POST  {site}{basepath}/services/package.json

  {"data":
    {"title" : "newtitle",
     "body"  : "newbody"
    }
  }

  Update    PUT   {site}{basepath}/services/package/{nid).json

  {"data":
    {"title" : "newtitle",        //optional
     "body"  : "newbody"          //optional
    }
  }

*****************************************************************/


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
  *  Function for index
  *
  *  @return object
  *  The results to render
  */
function  _ckanrest_index() {
  $results = array();
  $query = "SELECT nid from {node}
            WHERE type = 'ckan_package'";
  $resource = db_query($query);
  while ($row = db_fetch_array($resource)) $results[] = $row['nid'];
  return $results;
}


 /**
  *  Function for create
  *
  *  The node_save function here will not invoke hook_insert, hook_update. This is what we want in
  *  this case, as we only want to make a blank ckan_package node and ckan will take care of the
  *  rest of the update. node_save will invoke any hook_nodeapi hooks.
  *
  */
function  _ckanrest_create($data) {

  $response = array();
  // Check node options to see whether to publish by default.
  $package_options = variable_get('node_options_ckan_package', '1');
  $publish = in_array('status', $package_options);

  $pnode = new stdClass();
  $pnode->type = 'ckan_package';
  $pnode->title = $data['title'];
  $pnode->body =  $data['body'];
  $pnode->uid = 1;
  $pnode->name = "admin";
  $pnode->status = $publish;
  node_save($pnode);

  //Check the node has been saved
  if (isset($pnode->nid)) {
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
    node_delete($nid);

    //check if you have access to delete the node

    return array('deleted'=>$nid, 'more' =>$result['nid']);
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

  // Check the node exists.
  if (!$node->nid) {return services_error('Not a node.', 404);}

  // Check the node is the correct type.
  if (!$node->type == 'ckan_package') {return services_error('Not a package node.', 406);}

  // Update title, body, tags
  $node->title = $data['title'] ?  $data['title']: $node->title ;
  $node->body = $data['body'] ?  $data['body'] : $node->body ;

  node_save($node);
  return $node;
}

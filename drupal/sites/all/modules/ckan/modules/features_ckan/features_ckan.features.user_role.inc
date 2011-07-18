<?php

/**
 * Implementation of hook_user_default_roles().
 */
function features_ckan_user_default_roles() {
  $roles = array();

  // Exported role: package maintainer
  $roles['package maintainer'] = array(
    'name' => 'package maintainer',
  );

  // Exported role: package manager
  $roles['package manager'] = array(
    'name' => 'package manager',
  );

  return $roles;
}

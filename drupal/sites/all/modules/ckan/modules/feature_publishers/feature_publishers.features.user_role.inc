<?php

/**
 * Implementation of hook_user_default_roles().
 */
function feature_publishers_user_default_roles() {
  $roles = array();

  // Exported role: package editor
  $roles['package editor'] = array(
    'name' => 'package editor',
  );

  // Exported role: publisher administrator
  $roles['publisher administrator'] = array(
    'name' => 'publisher administrator',
  );

  return $roles;
}

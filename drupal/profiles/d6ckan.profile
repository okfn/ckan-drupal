<?php
/**
* Return a description of the profile for the initial installation screen.
*
* @return
*   An array with keys 'name' and 'description' describing this profile.
*/
function ckan_profile_details() {
  return array(
    'name' => 'Ckan',
    'description' => 'Base install profile for CKAN.',
  );
}

/**
* Return an array of the modules to be enabled when this profile is installed.
*
* @return
*  An array of modules to be enabled.
*/
function ckan_profile_modules() {
  return array(
    // Enable required core modules first.
    'block',
    'comment',
    'dblog',
    'filter',
    'help',
    'menu',
    'node',
    'path',
    'search',
    'system',
    'taxonomy',
    'upload',
    'user',
    'admin_menu',
    'ckan',
    'views_ui',
  );
}


/**
 * Implementation of hook_profile_tasks().
 */
function ckan_profile_tasks(&$task, $url) {

}


?>
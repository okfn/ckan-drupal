<?php
require_once("lib/ckan.lib.inc");

$ckan = new Ckan('http://127.0.0.1:5000/','bf9b6b2a-136e-40f3-826f-f5d9bd819d6b');
$ckan->enableDebug(1);
//$data = $ckan->search('aaa');

$data ='{
				"name": "iighi",
				"title": "iighi",
				"url": "String",
				"notes": "notes",
				"maintainer": "maintainer",
				"maintainer_email": "email",
				"license_id": "String"
			}';
$ckan->setPackage($data);


/*
  $ckan = new Ckan('34896250-b652-4d08-b802-58bcd28bb74a');
  //$ckan->enableDebug(1);

  $data = '{
				"name": "name_strinasg",
				"title": "Strigfhng"
			}';
	$return = $ckan->post_package_register($data);
*/


?>
<?php

/**
 *  CKAN connection class
 *
 *  Original work by Sean Burlington sean@practicalweb.co.uk
 *
 */

/** Example usage
 *
		require_once("ckan.php");
		$ckan = new Ckan('http://dgu-live.okfn.org/','user','pass');
		$ckan->enableDebug(1);
		$data = $ckan->search('mypackage');
		print_r($data);
 */


class Ckan {

  /*
   * URL to the ckan instance
   */
  private $baseurl = '';

 /*
  * CKAN API key for PUT, POST operations
  */
  private $apikey = '';


  private $debugmode = FALSE;


  private $httpcodes = array(
    100 => 'Continue',
    101 => 'Switching Protocols',
    200 => 'OK',
    201 => 'Created',
    202 => 'Accepted',
    203 => 'Non-Authoritative Information',
    204 => 'No Content',
    205 => 'Reset Content',
    206 => 'Partial Content',
    300 => 'Multiple Choices',
    301 => 'Moved Permanently',
    302 => 'Found',
    303 => 'See Other',
    304 => 'Not Modified',
    305 => 'Use Proxy',
    307 => 'Temporary Redirect',
    400 => 'Bad Request',
    401 => 'Unauthorized',
    402 => 'Payment Required',
    403 => 'Forbidden',
    404 => 'Not Found',
    405 => 'Method Not Allowed',
    406 => 'Not Acceptable',
    407 => 'Proxy Authentication Required',
    408 => 'Request Time-out',
    409 => 'Conflict (e.g. name already exists)',
    410 => 'Gone',
    411 => 'Length Required',
    412 => 'Precondition Failed',
    413 => 'Request Entity Too Large',
    414 => 'Request-URI Too Large',
    415 => 'Unsupported Media Type',
    416 => 'Requested range not satisfiable',
    417 => 'Expectation Failed',
    500 => 'Internal Server Error',
    501 => 'Not Implemented',
    502 => 'Bad Gateway',
    503 => 'Service Unavailable',
    504 => 'Gateway Time-out',
    505 => 'HTTP Version not supported',
  );


  /*
   * Resources available in the API.
   *
   * @var resources
   * @link http://packages.python.org/ckan/api/version2.html CKAN api reference @endlink
   */
  private $resources = array(
    'Package Register'  =>                '/rest/package',
    'Package Entity'  =>                  '/rest/package/%s',    //PACKAGE-REF
    'Group Register'  =>                  '/rest/group',
    'Group Entity'  =>                    '/rest/%s',    //GROUP-NAME
    'Tag Register'  =>                    '/rest/tag',
    'Tag Entity'  =>                      '/rest/tag/%s',     //TAG-NAME
    'Rating Register'  =>                 '/rest/Rating',
    'Rating Entity'  =>                   '/rest/Rating/%s',    //PACKAGE-REF
    'Package Relationships Register'  =>  'rest/package/%s/relationships',    //PACKAGE-REF
    'Package Relationships Register'  =>  '/rest/package/%s/relationships/%s',    //PACKAGE-REF, PACKAGE-REF
    'Package Relationships Entity'  =>    '/rest/package/%s/%s/%s',    //PACKAGE,REFRELATIONSHIP-TYPE,PACKAGE-REF
    'Package’s Revisions Entity'  =>      '/rest/package/%s/revisions',    //PACKAGE-REF
    'Revision Register'  =>               '/rest/revision',
    'Revision Entity'  =>                 '/rest/revision/%s',    //REVISION-ID
    'License List'  =>                    '/rest/licenses',#
    'drupal package create' =>            '/api/action/drupal_package_create',
    'drupal package update' =>            '/api/action/drupal_package_update',
    'api version' =>                      '/api',
  );





  public function __construct($url=null, $apikey=null){
    if ($url){ $this->baseurl=$url; }
    if ($apikey) { $this->apikey = $apikey; }
  }

  public function enableDebug()  { $this->debugmode = TRUE; }
  public function disableDebug() { $this->debugmode = FALSE; }


  private function transfer($url, $method='GET', $data=null) {

    $ch = curl_init($url);

    $ch_options = array(
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_HEADER => FALSE,
      CURLOPT_TIMEOUT => 30,
      );

    if (in_array($method, array('POST','PUT'))) {
      if (!$this->apikey) {throw new CkanException("No API KEY.");}

      $ch_options[CURLOPT_HTTPHEADER] =  array(
      	'Authorization: '.$this->apikey,
        //'Accept: application/json',
      );
      $ch_options[CURLOPT_POSTFIELDS] = $data;
      $ch_options[CURLOPT_CUSTOMREQUEST] = 'POST';
    }


    curl_setopt_array($ch, $ch_options);
    $result = curl_exec($ch);
    $info = curl_getinfo($ch);
    curl_close($ch);

    // Provide useful output when debugmode is turned on.
    if ($this->debugmode) { var_dump($info, $result, $data); }

    if (!in_array($info['http_code'], array(200,201))) {
      throw new CkanException($this->_http_exception_message($info['http_code']), $info['http_code']);
    }
    if (!$result){
      throw new CkanException("No Result");
    }
    return json_decode($result);
  }

  public function createPackage($json){
    $url=$this->baseurl.$this->resources['drupal package create'];
    $package = $this->transfer($url, 'POST', $json);
    return $package;
  }

  public function updatePackage($json){
    $url=$this->baseurl.sprintf($this->resources['drupal package update']);
    $package = $this->transfer($url, 'POST', $json);
    return $package;
  }

  public function getApiVersion(){
    $url=$this->baseurl.sprintf($this->resources['api version']);
    $package = $this->transfer($url);
    return $package;
  }

  private function _http_exception_message($error_code) {
    $exception_message = 'CKAN HTTP error '.$error_code . ' : ' . $this->httpcodes["{$error_code}"];
    return $exception_message;
  }

}

class CkanException extends Exception{}

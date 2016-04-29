<?php

/**
 * @file commerce_dapi_orders.restclient_function.inc
 * Get all function for dapi interactions.
 */

/**
 * Search subject in Diapason.
 *
 * @param $data
 *  An array with values:
 *   - firmName: ;
 *   - vatID: ;
 *   - taxpayerID: ;
 *   - email: ;
 *  This key is unique and required.
 *
 * @return object
 */
function commerce_dapi_orders_search_subject($data = array()) {

  $resource_path = 'soggetti/cerca-soggetto';

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'body' => drupal_json_encode($data),
    'headers' => array(
      "Content-Type" => "application/json",
    ),
  );

  $response = restclient_post($resource_path, $variables);

  return $response;
}

/**
 * Retrieve subject information.
 *
 * @param $subject_id
 *  SubjectID
 * @return object
 *  Response from API Diapason.
 */
function commerce_dapi_orders_retrieve_subject($subject_id) {

  $resource_path = 'soggetti/dati-generali-soggetti/' . check_plain($subject_id);

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'headers' => array(
      "Content-Type" => "application/json",
    ),
  );
  $response = restclient_get($resource_path, $variables);

  return $response;
}

/**
 * Retrieve subject addresses in Diapason.
 *
 * @param $subject_id
 *  SubjectID
 * @return object
 *  Response from API Diapason.
 */
function commerce_dapi_orders_retrieve_subject_addresses($subject_id) {

  $resource_path = 'soggetti/indirizzi-soggetti/' . check_plain($subject_id);

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'headers' => array(
      "Content-Type" => "application/json",
    ),
  );
  $response = restclient_get($resource_path, $variables);

  return $response;
}

/**
 * Insert data to create soubject in ERP.
 *
 * @param array $data
 *  Data subject
 * @return object
 *  Response from ERP.
 */
function commerce_dapi_orders_insert_subject($data = array()) {

  $resource_path = 'soggetti/inserimento-soggetto';

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'body' => drupal_json_encode($data),
    'headers' => array(
      "Content-Type" => "application/json",
    ),
  );

  $response = restclient_post($resource_path, $variables);

  return $response;
}

/**
 * Insert data order in ERP.
 *
 * @param array $data
 *  Data Order.
 * @return object
 *  Response from ERP.
 */
function commerce_dapi_orders_insert_order($data = array()) {

  $resource_path = 'ordini/inserimento-ordine';

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'body' => $data,
    'headers' => array(
      "Content-Type" => "application/x-www-form-urlencoded",
    ),
  );

  $response = restclient_post($resource_path, $variables);

  return $response;
}

/**
 * Insert Discount into Diapason Order.
 *
 * @param $discount_value
 *   Value of discount. (Use point for decimal, no comma).
 * @param $diapason_order_id
 *   Id order of ERP.
 * @param string $type
 *   Type of discount [amount,fixed].
 * @return object
 *   Response from ERP.
 */
function commerce_dapi_orders_insert_discount($discount_value, $diapason_order_id, $type = 'amount') {

  $resource_path = "ordini/inserimento-sconto-ordine/$type/$discount_value/$diapason_order_id";

  $variables = array(
    'endpoint' => variable_get('commerce_dapi_orders_hostname', 'http://localhost/'),
    'headers' => array(
      "Content-Type" => "application/json",
    ),
  );
  $response = restclient_get($resource_path, $variables);

  return $response;
}

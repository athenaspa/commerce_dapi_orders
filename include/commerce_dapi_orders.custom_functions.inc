<?php

/**
 * @file commerce_dapi_orders.custom_functions.inc
 * Container all custom functions for module.
 */

/**
 * La funzione, letta la data passata in timestamp, calcola:
 * +1 giorno per i giorni Lun->Giov
 * +2 se sabato
 * +3 se venerdì
 */
function _commerce_dapi_orders_find_delivery_date_for_individual() {

  // recupero il giorno della settimana e avvio lo switch dmy
  $dw = date("w");
  switch ($dw) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      $delivery_date = date("dmy", mktime(0, 0, 0, date("m"), date("d") + 1, date("Y")));
      break;
    case 5:
      $delivery_date = date("dmy", mktime(0, 0, 0, date("m"), date("d") + 3, date("Y")));
      break;
    case 6:
      $delivery_date = date("dmy", mktime(0, 0, 0, date("m"), date("d") + 2, date("Y")));
      break;
  }

  return $delivery_date;

}

/**
 * Check if order is freeshipping or not
 */
function _is_freeshipping($wrapper) {

  foreach ($wrapper->commerce_line_items as $line_item_wrapper) {
    if ($line_item_wrapper->type->value() == 'shipping') {
      return 'paid';
    }
  }

  return 'unpaid';
}

/**
 * Controll if country is EU
 */
function _commerce_dapi_orders_is_EU($countrycode) {
  $eu_countrycodes = array(
    'AL',
    'AD',
    'AM',
    'AT',
    'BY',
    'BE',
    'BA',
    'BG',
    'CH',
    'CY',
    'CZ',
    'DE',
    'DK',
    'EE',
    'ES',
    'FO',
    'FI',
    'FR',
    'GB',
    'GE',
    'GI',
    'GR',
    'HU',
    'HR',
    'IE',
    'IS',
    'IT',
    'LT',
    'LU',
    'LV',
    'MC',
    'MK',
    'MT',
    'NO',
    'NL',
    'PL',
    'PT',
    'RO',
    'RU',
    'SE',
    'SI',
    'SK',
    'SM',
    'TR',
    'UA',
    'VA',
  );
  return (in_array($countrycode, $eu_countrycodes));
}

/**
 * Gets the list of countries from the locale settings in Drupal.
 *
 * @return array An array of countries.  The keys are the 2-letter
 *   abbreviations and the values are the full country names.
 */
function _commerce_dapi_countries() {
  $countries = &drupal_static(__FUNCTION__);
  if (empty($countries)) {
    include_once('includes/locale.inc');
    $countries = country_get_list();
  }
  return $countries;
}

/**
 * Gets the name of the country with the given abbreviation.
 *
 * @param string $country The 2-letter abbreviation of the country.
 * @return string The name of the country, or FALSE.
 */
function _commerce_dapi_orders_country($country) {
  $countries = _commerce_dapi_countries();

  // Country abbreviations will always be two uppercase letters. 
  $country = drupal_strtoupper($country);
  if (!empty($country) && isset($countries[$country])) {
    return check_plain($countries[$country]);
  }
  return check_plain($country);
}

/**
 * Gets the abbreviation of the country with the given name
 *
 * @param string
 *   The name of the country.
 * @return string $country
 *   The 2-letter abbreviation of the country, or FALSE.
 */
function _commerce_dapi_country_abbr($country) {
  $countries = array_flip(array_map('strtolower', _commerce_dapi_countries()));

  if (isset($countries[strtolower($country)])) {
    return check_plain($countries[strtolower($country)]);
  }
  return check_plain($country);
}

/**
 * Gets the list of states in the given country.
 *
 * @param string $country The 2-letter abbreviation of the country.
 *
 * @return array An array of countries.  The keys are the 2-letter
 *   abbreviations and the values are the full country names.
 */
function _commerce_dapi_states($country) {
  $states = &drupal_static(__FUNCTION__);
  $country = drupal_strtoupper($country);
  if (!isset($states[$country])) {
    $cache = cache_get('commerce_dapi_states');
    if ($cache) {
      $states = $cache->data;
    }
  }
  if (!isset($states[$country])) {
    $format = addressfield_generate(array('country' => $country), array('address'), array('mode' => 'render'));

    if (isset($format['locality_block']['administrative_area']['#options'])) {
      $states[$country] = $format['locality_block']['administrative_area']['#options'];
    }
    else {
      $states[$country] = array();
    }
    cache_set('commerce_dapi_states', $states);
  }
  return $states[$country];
}

/**
 * Gets the name of the state with the given abbreviation.
 *
 * @param string $country The 2-letter abbreviation of the country.
 * @param string $state The 2-letter abbreviation of the state.
 * @return string The name of the state, or FALSE.
 */
function _commerce_dapi_orders_state($country, $state) {
  $states = _commerce_dapi_states($country);

  // State abbreviations will usually be two uppercase letters. 
  $state = drupal_strtoupper($state);
  if (!empty($state) && !empty($states[$state])) {
    return check_plain($states[$state]);
  }
  return check_plain($state);
}

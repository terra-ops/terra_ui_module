<?php
/**
 * @file
 * terra_ui.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function terra_ui_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function terra_ui_node_info() {
  $items = array(
    'app' => array(
      'name' => t('App'),
      'base' => 'node_content',
      'description' => t('A Terra app is equivalent to a Drupal distribution.'),
      'has_title' => '1',
      'title_label' => t('Machine name'),
      'help' => '',
    ),
    'environment' => array(
      'name' => t('Environment'),
      'base' => 'node_content',
      'description' => t('A Terra environment is equivalent to a site.'),
      'has_title' => '1',
      'title_label' => t('Machine name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

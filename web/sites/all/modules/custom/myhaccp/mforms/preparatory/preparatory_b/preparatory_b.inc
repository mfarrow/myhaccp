<?php

/**
 * @file
 * Preparatory B stage form and validation handler.
 */

/**
 * Preparatory B.
 */
function preparatory_b(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_1';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_b');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-b';

  // Wrap the form section in a fieldset.
  $form['preparatory_b'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_b']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('You need to provide details of support by management to an ongoing HACCP study.'),
  );

  $form['preparatory_b']['b_1'] = array(
    '#type' => 'checkboxes',
    '#title' => t('1. What documented evidence do you have to show the support of the food business operator or senior management to the food safety management system based on HACCP principles?'),
    '#help_link' => 14,
    '#help_text' => t("Where in your company could you look for evidence to demonstrate that senior management are engaged and dedicated to the development of an ongoing HACCP study."),
    '#options' => array(
      'N/A - I am the management and can confirm that I am committed.' => t('N/A - I am the management and can confirm that I am committed.'),
      'A Food Safety Policy has been drawn up and signed by management.' => t('A Food Safety Policy has been drawn up and signed by management.'),
      'Senior management document, support and communicate their food safety policies.' => t('Senior management document, support and communicate their food safety policies.'),
      'Minutes of HACCP team meetings.' => t('Minutes of HACCP team meetings.'),
      'Senior management support the work of the HACCP team.' => t('Senior management support the work of the HACCP team.'),
      'Resources identified by the HACCP team are made available as required to develop, implement and maintain the HACCP system.' => t('Resources identified by the HACCP team are made available as required to develop, implement and maintain the HACCP system.'),
      'Training takes place for HACCP studies.' => t('Training takes place for HACCP studies.'),
    ),
    '#default_value' => array_get($values, 'preparatory_b.b_1', array()),
    '#attributes' => array(
      'data-parsley-group' => 'checkgroup',
      'data-parsley-either' => '#edit-container-prep-b-support .form-item input,#edit-container-prep-b-evidence',
      'data-parsley-either-message' => t('Please choose at least one option in question 1 or add some content in question 2.'),
      'data-parsley-error-container' => '.form-item-container-prep-b-support',
    ),
  );

  $form['preparatory_b']['b_2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Provide details of anything else that shows management commitment to the HACCP based food safety management system.'),
    '#help_link' => 14,
    '#help_text' => t("State anything else that would demonstrate you have management commitment."),
    '#default_value' => array_get($values, 'preparatory_b.b_2', FALSE),
    '#attributes' => array(
      'data-parsley-either' => '#edit-container-prep-b-support .form-item input,#edit-container-prep-b-evidence',
      'data-parsley-message' => t('Please choose at least one option in question 1 or add some content in question 2.'),
      'data-parsley-required' => TRUE,
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_b_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  $messages = array();

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $evidence = new Validation($form, $form_state, 'preparatory_b.b_2');
  $support = new Validation($form, $form_state, 'preparatory_b.b_1');
  if (!$evidence->fieldIsNotEmpty() && !$support->fieldIsNotEmpty()) {
    $messages = array(
      'validation_messages' => array(t('Please choose at least one option in question 1 or add some content in question 2.')),
    );
    $validator->passed = FALSE;
  }

  $validator->setErrorMessages(($messages));
  $form_state = $validator->getFormState();
}

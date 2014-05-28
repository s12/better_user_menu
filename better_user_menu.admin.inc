<?php

/*
 * @form builder
 * hook_admin_settings()
 */
function better_user_menu_admin_settings($form, &$form_state){
	$enabled = variable_get('better_user_menu_enabled',TRUE);

	$login_shown = variable_get('better_user_menu_login_shown',TRUE);
	$login_text = variable_get('better_user_menu_login_text','Log in');
	$descripiton_login = variable_get('better_user_menu_login_title','Click here to log in');

	$reg_shown = variable_get('better_user_menu_reg_shown',TRUE);
	$reg_text = variable_get('better_user_menu_reg_text','Sign up');
	$descripiton_register = variable_get('better_user_menu_reg_title','Click here to sign up');

	$form['better_user_menu_enabled'] = array(
		'#type' => 'checkbox',
		'#title' => 'Enable better user menu?',
		'#default_value' => $enabled,
		'#description' => '(Checking / Unchecking) this box will (Enable / Disable) Better User Menu Functionality',
	);

	// Login settings
	$form['better_user_menu_login'] = array(
		'#type' => 'fieldset',
		'#title' => 'Log in:',
	);

	$form['better_user_menu_login']['better_user_menu_login_shown'] = array(
		'#type' => 'checkbox',
		'#title' => 'Show "Log in" menu item to anonymous users?',
		'#default_value' => $login_shown,
	);

	$form['better_user_menu_login']['better_user_menu_login_text'] = array(
		'#type' => 'textfield',
		'#title' => '"Log in" menu item link text',
		'#default_value' => $login_text,
	);

	$form['better_user_menu_login']['better_user_menu_login_title'] = array(
		'#type' => 'textfield',
		'#title' => '"Log in" menu item link attribute title',
		'#default_value' => $descripiton_login,
	);

	// Register settings
	$form['better_user_menu_register'] = array(
		'#type' => 'fieldset',
		'#title' => 'Sign Up:',
	);

	$form['better_user_menu_register']['better_user_menu_reg_shown'] = array(
		'#type' => 'checkbox',
		'#title' => 'Show "Sign up" menu item to anonymous users?',
		'#default_value' => $reg_shown,
	);

	$form['better_user_menu_register']['better_user_menu_reg_text'] = array(
		'#type' => 'textfield',
		'#title' => '"Sign up" menu item link text',
		'#default_value' => $reg_text,
	);

	$form['better_user_menu_register']['better_user_menu_reg_title'] = array(
		'#type' => 'textfield',
		'#title' => '"Sign up" menu item link `title` attribute',
		'#default_value' => $reg_title,
	);

	return system_settings_form($form);
}

/*
 * @form validate
 * hook_validate()
 */
function better_user_menu_admin_settings_validate($form, &$form_state){
	$bum = 'better_user_menu_';

	$bum_login_shown = $form_state['values'][$bum.'login'][$bum.'login_shown'];
	$bum_login_text = $form_state['values'][$bum.'login'][$bum.'login_text'];
	$bum_login_title = $form_state['values'][$bum.'login'][$bum.'login_title'];

	$bum_reg_shown = $form_state['values'][$bum.'register'][$bum.'reg_shown'];
	$bum_reg_text = $form_state['values'][$bum.'register'][$bum.'reg_text'];
	$bum_reg_title = $form_state['values'][$bum.'register'][$bum.'reg_title'];

	//Fatal errors
	if(empty($bum_login_text) && $bum_login_shown){
		form_set_error($bum.'login_text', t('"@login" menu item link text can not be empty.', array('@login' => variable_get($bum.'login_text','Log in'),)));
	}

	if(empty($bum_reg_text) && $bum_reg_shown){
		form_set_error($bum.'reg_text', t('"@register" menu item link text can not be empty.', array('@register' => variable_get($bum.'reg_text','Sign up'),)));
	}

	//Notices
	if(!$bum_login_shown){
		if((!empty($bum_login_text)) || (!empty($bum_login_title))){
			drupal_set_message(t('"@login" menu item is disabled.', array('@login' => variable_get($bum.'login_text','Log in'),)),'warning');
		}
	}

	if(!$bum_reg_shown){
		if((!empty($bum_reg_text)) || (!empty($bum_reg_title))){
			drupal_set_message(t('"@register" menu item is disabled.',array('@register' => variable_get($bum.'reg_text','Sign up'),)),'warning');
		}
	}

	if(empty($bum_login_title)){
		drupal_set_message(t('"@login" menu item title attribute not set.', array('@login' => variable_get($bum.'login_text','Log in'),))),'warning');
	}

	if(empty($bum_reg_title)){
		drupal_set_message(t('"@register" menu item title attribute not set.', array('@register' => variable_get($bum.'reg_text','Sign up'),))),'warning');
	}
}
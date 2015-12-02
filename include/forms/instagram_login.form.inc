<?php
	function instagram_login_form($form, &$form_state,$instagramBookModel){

		$form['instagram_login']['description'] = array(
			'#type' => "item",
			'#description' => t("If you update your Client ID, <strong>always</strong> authorize it before pressing save.")
		);

		$form['instagram_login']['instagram_client_id'] = array(
		  '#type' => 'textfield',
		  '#title' => t('Instagram Client Id'),
		  '#size' => 40,
		  '#maxlength' => 255,
		  '#required' => TRUE,
			'#default_value' => isset($instagramBookModel->instagram_client_id)? $instagramBookModel->instagram_client_id: ""
		);

		$form['instagram_login']['verify_client_id'] = array(
			'#type' => 'submit',
			'#value' => t('Authorize Client ID'),
			'#submit' => array('instagram_book_verify_client_id'),
		);

		return $form;
	}

	function resume_ajax_callback($form, $form_state){
		return $form['instagram_login'];
	}

	function instagram_book_verify_client_id($form, &$form_state){
		global $base_url;
		$redirect_url = $base_url."/admin/structure/instagram-book";
		$instagram_client_id = $form_state['values']['instagram_login']['instagram_client_id'];

		$dataModels = InstagramBookModel::getMapper()->findAll();		
		$instagramBookModel = null;
		if(count($dataModels) > 0){
			$instagramBookModel = $dataModels[0];
			$instagramBookModel->updateFields($form_state['values']['instagram_login']);
			InstagramBookModel::getMapper()->setModel($instagramBookModel)->save();
		}else{
			$instagramBookModel = InstagramBookModel::createObject($form_state['values']['instagram_login']);
			InstagramBookModel::getMapper()->setModel($instagramBookModel)->save();
		}

		drupal_set_message("If the page reloaded successfully, it means the authorization succeeded. Continue with the Authentication."); 

		$url = "https://api.instagram.com/oauth/authorize?client_id=$instagram_client_id&redirect_uri=$redirect_url&scope=basic&response_type=code";
		drupal_goto($url, array('external' => TRUE));
		$form_state['rebuild'] = TRUE;
	}

?>

<?php

module_load_include('inc', 'instagram_book', 'include/forms/instagram_login.form');

	function instagram_book_fields_form($form, &$form_state) {
		$form['#tree'] = TRUE;

		$dataModels = InstagramBookModel::getMapper()->findAll();		
		$instagramBookModel = null;
		if(count($dataModels) > 0){
			$instagramBookModel = $dataModels[0];
		}

		$form = array_merge($form,instagram_login_form($form, $form_state,$instagramBookModel));

		if(isset($_GET['code']) || (isset($instagramBookModel) && strlen($instagramBookModel->instagram_client_secret) > 1)){			
			$form['instagram_client_secret'] = array(
				 '#title' => t('Instagram Client Secret'),
		     '#type' => 'textfield',
		     '#required' => TRUE,
				 '#default_value' => isset($instagramBookModel->instagram_client_secret) ? $instagramBookModel->instagram_client_secret : ""
		  );

			$form['submit_button'] = array(
				'#type' => 'submit',
				'#value' => t('Authenticate & Save'),
			);
		}

		$form['instagram_access_token'] = array(
			'#type' => "hidden",
			'#value' => isset($instagramBookModel->instagram_access_token) ? $instagramBookModel->instagram_access_token : ""
		);
		
		return $form;
	}

	function instagram_book_fields_form_submit($form, &$form_state) {
		$instagram_client_secret =  $form_state['values']['instagram_client_secret'];
		$dataModels = InstagramBookModel::getMapper()->findAll();		

		if(count($dataModels) > 0){
			$instagramBookModel = $dataModels[0];
			$instagramBookModel->updateFields($form_state['values']);
			$instagramBookModel->updateFields($form_state['values']['instagram_login']);
			if(isset($_GET['code']) || strlen($instagramBookModel->instagram_access_token) == 0){
				$instagramResponse = InstagramBookApiHelper::authenticateInstagramCredentials($instagramBookModel,$_GET['code']);
				if($instagramResponse){
					if(isset($instagramResponse->access_token)){
						$instagramBookModel->instagram_access_token = $instagramResponse->access_token;
						InstagramBookModel::getMapper()->setModel($instagramBookModel)->save();
						drupal_set_message("Your Instagram credentials are valid and are being saved successfully."); 
					}else{
						drupal_set_message("Failed to save: ".$instagramResponse->error_message,"error"); 						
					}
				}
			}
		}

    return $form;

	}

?>

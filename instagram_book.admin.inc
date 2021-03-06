<?php

module_load_include('inc', 'instagram_book', 'include/forms/instagram_login.form');

	function instagram_book_fields_form($form, &$form_state) {
		$form['#tree'] = TRUE;

		$form['description'] = array(
			'#type' => "item",
			'#description' => t("First authorize your Client ID and then press Authenticate & Save. When the authentication succeeds, a block view is created to assign it in any page. ")
		);

		$dataModels = InstagramBookModel::getMapper()->findAll();		
		$instagramBookModel = null;
		if(count($dataModels) > 0){
			$instagramBookModel = $dataModels[0];
		}

		$form = array_merge($form,instagram_login_form($form, $form_state,$instagramBookModel));

		$form['instagram_album_cover_image'] = array(
			'#title' => t('Album Cover Image'),
			'#type' => 'managed_file',
			'#description' => t('Upload a 520x520 cover image.'),
			'#upload_location' => 'public://',
			'#default_value' => isset($instagramBookModel->image_id) ? $instagramBookModel->image_id : null
		);

		if(isset($_GET['code']) || (isset($instagramBookModel) && strlen($instagramBookModel->instagram_client_secret) > 1)){			
			$form['instagram_client_secret'] = array(
				 '#title' => t('Instagram Client Secret'),
		     '#type' => 'textfield',
		     '#required' => TRUE,
				 '#default_value' => isset($instagramBookModel->instagram_client_secret) ? $instagramBookModel->instagram_client_secret : ""
		  );

			$form['no_of_images'] = array(
		     '#type' => 'textfield',
				 '#title' => t('No of images you want to be shown in the album'),
				 '#description' => t("If you update this value, remember to clear the custom cache file to get the correct number of images."),
		     '#required' => TRUE,
				 '#size' => 4,
				 '#element_validate' => array('instagram_book_integer_validate'),
				 '#default_value' => isset($instagramBookModel->no_of_images) ? $instagramBookModel->no_of_images : 20
		  );

			$form['cache_lifetime'] = array(
		     '#type' => 'textfield',
				 '#title' => t('Cache lifetime'),
				 '#description' => t("Set the lifetime that Drupal will keep in cache the Instagram API Results for faster loading. The value is in seconds."),
		     '#required' => TRUE,
				 '#size' => 4,
				 '#element_validate' => array('instagram_book_integer_validate'),
				 '#default_value' => isset($instagramBookModel->cache_lifetime) ? $instagramBookModel->cache_lifetime : 360
		  );

			$form['clear_cache_file'] = array(
				'#type' => 'submit',
				'#value' => t('Clear Instagram cache'),
				'#submit' => array('instagram_book_clear_cache'),
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
		
		$form['instagram_user_id'] = array(
			'#type' => "hidden",
			'#value' => isset($instagramBookModel->instagram_user_id) ? $instagramBookModel->instagram_user_id : ""
		);

		return $form;
	}

	function instagram_book_integer_validate($element, $form_state){
		if(strlen($element['#value']) == 0){
			return;
		}
		if(!is_numeric($element['#value'])){
			form_error($element, t('You must enter a number.'));	
		}
	}

	function instagram_book_fields_form_submit($form, &$form_state) {

		$file = InstagramBookImageHelper::handleImageFile($form['instagram_album_cover_image']['#default_value'],
$form_state['values']['instagram_album_cover_image'],"instagram_book","instagram_album_cover_image");

		$instagram_client_secret =  $form_state['values']['instagram_client_secret'];
		$dataModels = InstagramBookModel::getMapper()->findAll();		

		if(count($dataModels) > 0){
			$instagramBookModel = $dataModels[0];
			$instagramBookModel->updateFields($form_state['values']);
			$instagramBookModel->image_id = isset($file) ? $file->fid : null;
			$instagramBookModel->updateFields($form_state['values']['instagram_login']);
			if(isset($_GET['code']) || strlen($instagramBookModel->instagram_access_token) == 0){
				$instagramResponse = InstagramBookApiHelper::authenticateInstagramCredentials($instagramBookModel,$_GET['code']);
				if($instagramResponse){
					if(isset($instagramResponse->access_token)){
						$instagramBookModel->instagram_access_token = $instagramResponse->access_token;
						$instagramBookModel->instagram_user_id = $instagramResponse->user->id;
						InstagramBookModel::getMapper()->setModel($instagramBookModel)->save();
						cache_clear_all(INSTAGRAM_BOOK_CACHE_NAME,INSTAGRAM_BOOK_CACHE_TYPE);	
						drupal_set_message("Your Instagram credentials are valid and are being saved successfully."); 
					}else{
						drupal_set_message("Failed to save: ".$instagramResponse->error_message,"error"); 						
					}
				}
			}else if (strlen($instagramBookModel->instagram_access_token) > 1){
				InstagramBookModel::getMapper()->setModel($instagramBookModel)->save();
				cache_clear_all(INSTAGRAM_BOOK_CACHE_NAME,INSTAGRAM_BOOK_CACHE_TYPE);	
				drupal_set_message("Successfully updated");
			}
		}

    return $form;

	}

	function instagram_book_clear_cache($form, &$form_state){
		$cachedData = cache_get(INSTAGRAM_BOOK_CACHE_NAME,INSTAGRAM_BOOK_CACHE_TYPE);
		if($cachedData){
			cache_clear_all(INSTAGRAM_BOOK_CACHE_NAME,INSTAGRAM_BOOK_CACHE_TYPE);	
			drupal_set_message("Cache has being cleared."); 			
		}else{
			drupal_set_message("The cache is not set.","warning"); 			
		}
	}

?>

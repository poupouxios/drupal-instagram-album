<?php

	function resume_main_fields_form($form, &$form_state) {
		global $base_url;

		$form['instagram_api_key'] = array(
			 '#title' => t('Instagram API key'),
       '#type' => 'textfield',
       '#required' => FALSE,
			 '#default_value' => ""
    );

		$form['submit_button'] = array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
		
		return $form;
	}

	function resume_main_fields_form_submit($form, &$form_state) {

		$instragram_api_key = $form_state['values']['instagram_api_key'];


		if(count($dataModels) == 0){
			$resumeMain = ResumeMainModel::createObject($form_state['values']);
			$resumeMain->image_id = isset($file) ? $file->fid : null;
			$resumeMainId = $resumeMain::getMapper()->setModel($resumeMain)->save();
			resume_set_subforms($form_state,$resumeMainId);
	    drupal_set_message("Your profile has been created. Visit the resume front page to view your changes."); 
		}else{
			$resumeMain = $dataModels[0];
			$resumeMain->updateFields($form_state['values']);
			$resumeMain->image_id = isset($file) ? $file->fid : null;
			$resumeMain::getMapper()->setModel($resumeMain)->save();
			resume_set_subforms($form_state,$resumeMain->id);
	    drupal_set_message("Your profile has been updated. Visit the resume front page to view your changes."); 
		}

    return $form;

	}

	function resume_set_subforms($form_state,$resumeMainId){
		foreach($form_state['values'] as $key => $dataSet){
			if(ResumeSubformHelper::doesFormExist($key)){
				$variantModelName = ResumeSubformHelper::getSubFormVariantModel($key);
				ResumeSubformModel::getMapper()->deleteAllBasedOn($resumeMainId,$variantModelName);
				$position = 0;
				foreach($dataSet as $data){
					if(is_array($data)){
						$formModel = $variantModelName::createObject($data);
						ResumeSubformModel::getMapper()->setSubformVariantModel($formModel)->saveSubformVariantData($resumeMainId,$position);
						$position++;
					}
				}
			}
		}
	}

?>

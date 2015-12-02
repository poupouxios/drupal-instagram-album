<?php

	class InstagramBookApiHelper{

		public static function isInstagramCredentialsValid($instagramBookModel){
			$url = "https://api.instagram.com/oauth/access_token";
			$headers = array('Content-Type' => 'application/x-www-form-urlencoded');
						     
			$data = array (
					'key' => $token,
					'id' => $node->nid,
					'action' => $action
					);
						         
			$response = drupal_http_request($url, $headers, 'POST', http_build_query($data, '', '&'));
		}	

	}

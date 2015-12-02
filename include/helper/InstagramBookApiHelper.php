<?php

	class InstagramBookApiHelper{

		public static function authenticateInstagramCredentials($instagramBookModel,$code){
			global $base_url;
			$url = "https://api.instagram.com/oauth/access_token";

			$data = array (
					 'client_id' => $instagramBookModel->instagram_client_id,
            'client_secret' => $instagramBookModel->instagram_client_secret,
            'grant_type' => 'authorization_code',
            'redirect_uri' => $base_url."/".ADMIN_URL,
            'code' => $code
					);

			$options = array(
				'method' => 'POST',
				'data' => drupal_http_build_query($data),
				'timeout' => 15,
				'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
			);
						         
			$response = drupal_http_request($url,$options);
			return json_decode($response->data);
		}	

	}

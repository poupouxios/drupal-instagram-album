<?php

	class InstagramBookModel extends InstagramBookBaseModel{
		public static $attributes = array(
			"id" => 0,
			"instagram_client_id" => "",
			"instagram_client_secret" => "",
			"instagram_code" => "",
			"instagram_access_token" => "",
			"instagram_user_id" => "",
			"cache_lifetime" => 0,
			"no_of_images" => 0,
			"created_at" => "NOW()",
			"updated_at" => "NOW()"
		);

	}

?>

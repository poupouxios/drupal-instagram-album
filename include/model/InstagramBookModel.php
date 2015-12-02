<?php

	class InstagramBookModel extends InstagramBookBaseModel{
		public static $attributes = array(
			"id" => 0,
			"instagram_client_id" => "",
			"instagram_client_secret" => "",
			"instagram_code" => "",
			"instagram_access_token" => "",
			"created_at" => "NOW()",
			"updated_at" => "NOW()"
		);

	}

?>

<?php
	$module_path =  drupal_get_path('module', 'instagram_book');
	$instagramApiUrl = "https://api.instagram.com/v1/users/".$instagramModel->instagram_user_id."/media/recent/?min_id=0&access_token=".$instagramModel->instagram_access_token;
	$cachedData = cache_get(INSTAGRAM_BOOK_CACHE_NAME,INSTAGRAM_BOOK_CACHE_TYPE);

	if($cachedData){
		$images = unserialize($cachedData->data);
	}
	else{
		$moreInstagramPhotos = true;
		$images = array();
		$count=0;
		while($moreInstagramPhotos)
		{
			$response = file_get_contents($instagramApiUrl);
			$result = json_decode($response);

			foreach(json_decode($response)->data as $item){
				$images[] = array(
					"title" => htmlspecialchars($item->caption->text),
					"src" => htmlspecialchars($item->images->standard_resolution->url)
				);
				$count++;
				if($count >= $instagramModel->no_of_images){
					break;
				}
			}
			if (!property_exists($result->pagination, 'next_url') || $count >= $instagramModel->no_of_images) {
				$moreInstagramPhotos = false;
			} else {
				$instagramApiUrl = $result->pagination->next_url;
			}
		
		}
		// Remove the last item, so we still have 
		// 32 items when when the cover is added
		array_pop($images);
	
		// Push the cover in the beginning of the array
		array_unshift($images,array("title"=>"Cover", "src"=>$module_path."/images/cover.jpg"));
	
		cache_set(INSTAGRAM_BOOK_CACHE_NAME,serialize($images),INSTAGRAM_BOOK_CACHE_TYPE,$instagramModel->cache_lifetime);
	}
	$totalPages = count($images);	
?>
<div class="col-sm-12" style="text-align:center"><div id="album" class="centerStart">
<?php	foreach($images as $i=>$image):?>
	<?php if($i < $instagramModel->no_of_images): ?>
		<div id="page<?php echo $i+1?>" class="page <?php echo ($i+1)%2? '' : 'leftPage'?>">
			<div class="img<?php echo $i+1?>">
				<span class="pageNum <?php echo ($i+1)%2? 'right' : 'left'?>"><?php echo $i+1?> // <?php echo $totalPages?></span>
				<img src="<?php echo $image['src']?>" alt="<?php echo $image['title']?>" />
			</div>
		</div>
	<?php else: ?>
		<?php break; ?>
	<?php endif; ?>
<?php endforeach; ?>	
</div>

<script type="text/javascript" src="<?= $module_path ?>/js/turn.min.js"></script>
<script type="text/javascript" src="<?= $module_path ?>/js/custom.js"></script>

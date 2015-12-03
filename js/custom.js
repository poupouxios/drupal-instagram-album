jQuery(document).ready(function ($) {

	var album = $('#album');
	loadAlbum();

	// turn.js defines its own events. We are listening
	// for the turned event so we can center the book
	album.bind('turned', function(e, page, pageObj) {
	
		if(page == 1 && $(this).data('done')){
			album.removeClass('fullPage');
			album.addClass('centerStart').removeClass('centerEnd');
		}
		else if (page == 80 && $(this).data('done')){
			album.removeClass('fullPage');
			album.addClass('centerEnd').removeClass('centerStart');
		}
		else {
			album.removeClass('centerStart centerEnd');
			album.addClass('fullPage');
		}
		
	});

	setTimeout(function(){
		// Leave some time for the plugin to
		// initialize, then show the book
		album.fadeTo(500,1);
	},1000);


	$(window).bind('keydown', function(e){
		
		// listen for arrow keys
		
		if (e.keyCode == 37){
			album.turn('previous');
		}
		else if (e.keyCode==39){
			album.turn('next');
		}

	});

	$(window).on("orientationchange",function(){
		var width = jQuery(".container").width();
		var album = jQuery('#album');
		width = width - 60;
		album.turn("size",width,width/2);
	});

});

function loadAlbum(){
	var album = jQuery('#album');
	var width = jQuery(".container").width();
	width = width - 60;
	album.turn({
			width: width,
			height: width/2,
			autoCenter: true,
			turnCorners: "bl,br",
	});
}

## Drupal Instagram Album

Drupal Instagram Album is a Drupal 7 module which by adding your Instagram Credentials it will give you a mobile friendly, album block. You can see my [Instagram Album](http://www.papasavvas.me/album), which is build using this module.

## Motivation

I started re-developing my site and I wanted to create an Instagram Album that will pull my photos and render them as an album flip book. However, as a developer, I wanted to create something that I will CRUD (Create, Read, Update , Delete) and to be flexible and convenient -  a phrase I use all the time :) .

So, I started creating this module. I setup all the necessary steps to authorize and authenticate with Instagram API and you can see the result in my [website](http://www.papasavvas.me/album) :)

## Requirements

The module requires to setup an Application in Instagram Developer page. Below I will explain how to set it up. Also, it uses [turn.js](http://www.turnjs.com/). Note that turnjs requires a [licence for commercial use](http://www.turnjs.com/get).

## Installation

### 1. Setup Instagram Application

* Go to `https://www.instagram.com/developer/` and login with your Instagram account credentials.
* Register for an application `https://www.instagram.com/developer/clients/register/`
* In the Valid redirect Urls remember to add this url `<base url of your site>/admin/structure/instagram-book`. For example if your site is `http://www.instagramalbum.com` then the URL will be `http://www.instagramalbum.com/admin/structure/instagram-book`. This will tell Instagram during the authorization to redirent back to the Instagram module and continue with the authentication. You can add as many URLs you want.
* If everything goes fine, Instagram will give you the below data:
  * Client ID code
  * Client Secret code

### 2. Install the module with Drupal classic way

* Download the zip file of this repo
* Add it to your `sites/all/modules` folder
* Go to `admin/modules` url and install the module
* You will find the module settings under `admin/structure/instagram-book`
* Add the Client ID in the `Instagram Client Id` field
* If you setup correctly the redirect URL, Instagram will redirect you back to the module to continue with the Authentication
* Add your Client Secret code in the `Instagram Client Secret` field
* Upload your cover photo to be displayed at the front of your album. The image needs to be square and the size ideally 520x520.
* Set how many images you want to be displayed in the album.
* Set how much time you want to cache the data from Instagram so you don't query every time the Instagram API to fetch the images. It uses the Drupal cache.
* After setting up all the fields, press `Authenticate & Save`
* A block will be created with the name `Instagram Book` which you can assign anywhere you want.

### 1. Add this module as a submodule (Assuming you are using version control for your Drupal website)

* Navigate first to your root folder of your Drupal website - where the index.php, cron.php etc files exist
* Execute this command to add this Drupal module as a submodule for your site `git submodule add https://github.com/poupouxios/drupal-instagram-album.git sites/all/modules/instagram-book`
* Then execute `git submodule init` and `git submodule update`. This will fetch the module and add it in the folder you specified
* The rest of the steps are the same like above ( From Go to.. step and after)

## License

This project is licensed under the MIT open source license.

## About the Author

[Valentinos Papasavvas](http://www.papasavvas.me/) works as a Senior Web Developer and iOS Developer in a company based in Sheffield/UK. You can find more on his [website](http://www.papasavvas.me/).

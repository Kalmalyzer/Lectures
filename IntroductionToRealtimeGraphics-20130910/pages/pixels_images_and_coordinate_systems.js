
"use strict";

var pixelsImagesAndCoordinateSystemsHTML = 
"<div id='pixelsImagesAndCoordinateSystemsHTML' class='container' style='text-align:center'>" +
"	<div class='row'>" +
"		<div class='span4'>" +
"			<p><h3>A pixel is the smallest unit you can control in an image</h3></p>" +
"			<p><h3>- you control the color of a pixel independently of other pixels</h3></p>" +
"			<p><h3>An image is a set of pixels</h3></p>" +
"			<p><h3>- you have a coordinate system in the image</h3></p>" +
"			<p><h3>- you refer to a pixel in an image via its coordinates</h3></p>" +
"			<p><h3>The <b>resolution</b> of an image is simply its dimensions, in pixels<p>" +
"			<p> " +
"		</div>" +
"		<div class='span8'>" +
"			<img src='images/image_with_coordinate_system.png'></img>" +
"		</div>" +
"	</div>" +
"	<div class='row'>" +
"		<div class='span12' style='display:inline-block; height:50px'>" +
"	</div>" +
"</div>";

function pixelsImagesAndCoordinateSystems_activate() {
	$("#dynamic_area").append(pixelsImagesAndCoordinateSystemsHTML);
}

function pixelsImagesAndCoordinateSystems_deactivate() {
	$("#pixelsImagesAndCoordinateSystemsHTML").remove();
}

function pixelsImagesAndCoordinateSystems_render() {
}

PowerPoint.append_page("Pixels, Images and Coordinate Systems", pixelsImagesAndCoordinateSystems_activate, pixelsImagesAndCoordinateSystems_deactivate, pixelsImagesAndCoordinateSystems_render);


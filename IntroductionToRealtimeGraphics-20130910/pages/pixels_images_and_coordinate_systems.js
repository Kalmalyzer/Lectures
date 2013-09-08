
"use strict";

var pixelsImagesAndCoordinateSystemsHTML = 
"<div id='pixelsImagesAndCoordinateSystemsHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6' style='margin-top:100px'>" +
"			<p>A pixel is the smallest unit you can control in an image</p>" +
"			<p><ul><li>you control the color of a pixel independently of other pixels</li></ul></p>" +
"			<p>An image is a set of pixels</h3></p>" +
"			<ul><li>you have a coordinate system in the image</li>" +
"			<li>you refer to a pixel in an image via its coordinates</li></ul>" +
"			<p>The <b>resolution</b> of an image is simply its dimensions, in pixels<p>" +
"			<p> " +
"		</div>" +
"		<div class='span6'>" +
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


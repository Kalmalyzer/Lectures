
"use strict";

var resolutionsAndRefreshRatesHTML = 
"<div id='resolutionsAndRefreshRatesHTML' class='container' style='text-align:center'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p><h3>Specs for a modern monitor:</h3></p>" +
"			<p><h3>Resolution: 1920 x 1080 pixels</h3></p>" +
"			<p><h3>Refresh rate: 60 Hz</h3></p>" +
"			<p><br></p> " +
"			<p><h3>Monitors usually accept a couple of lower resolutions, and automatically up-scale them</h3></p>" +
"		</div>" +
"		<div class='span6'>" +
"			<img src='images/monitor.jpg'></img>" +
"		</div>" +
"	</div>" +
"</div>";

function resolutionsAndRefreshRates_activate() {
	$("#dynamic_area").append(resolutionsAndRefreshRatesHTML);
}

function resolutionsAndRefreshRates_deactivate() {
	$("#resolutionsAndRefreshRatesHTML").remove();
}

function resolutionsAndRefreshRates_render() {
}

PowerPoint.append_page("Resolutions and refresh rates", resolutionsAndRefreshRates_activate, resolutionsAndRefreshRates_deactivate, resolutionsAndRefreshRates_render);


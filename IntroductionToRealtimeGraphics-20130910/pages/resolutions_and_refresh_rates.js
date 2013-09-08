
"use strict";

var resolutionsAndRefreshRatesHTML = 
"<div id='resolutionsAndRefreshRatesHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6' style='margin-top:100px'>" +
"			<p>Specs for a modern monitor:<br>" +
"				Resolution: 1920 x 1080 pixels</br>" +
"				Refresh rate: 60 Hz<br></p>" +
"			<p>Monitors usually accept a couple of lower resolutions, and automatically up-scale them</p>" +
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


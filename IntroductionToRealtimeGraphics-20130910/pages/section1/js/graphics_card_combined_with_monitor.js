
"use strict";

var graphicsCardCombinedWithMonitorHTML = 
"<div id='graphicsCardCombinedWithMonitorHTML' class='container' style='text-align:center'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>The graphics card has memory: that is where the image resides (the 'framebuffer')</p>" +
"			<p>The display circuitry fetches pixel data from the framebuffer, and sends it over the video cable - over and over again, at the appropriate rate.</p>" +
"		</div>" +
"		<div class='span6'>" +
"			<p>The monitor expects the stream of pixel data to arrive at a steady rate over the video cable - over and over again, and updates elements on the display accordingly.</p>" +
"		</div>" +
"	</div>" +
"	<div class='row'>" +
"		<div class='span12' style='display:inline-block; height:50px'>" +
"	</div>" +
"	<div class='row'>" +
"		<div class='span12'>" +
"			<img src='pages/section1/img/graphics_card_combined_with_monitor.jpg'></img>" +
"		</div>" +
"	</div>" +
"</div>";

function graphicsCardCombinedWithMonitor_activate() {
	$("#dynamic_area").append(graphicsCardCombinedWithMonitorHTML);
}

function graphicsCardCombinedWithMonitor_deactivate() {
	$("#graphicsCardCombinedWithMonitorHTML").remove();
}

function graphicsCardCombinedWithMonitor_render() {
}

PowerPoint.append_page("Graphics card combined with monitor", graphicsCardCombinedWithMonitor_activate, graphicsCardCombinedWithMonitor_deactivate, graphicsCardCombinedWithMonitor_render);


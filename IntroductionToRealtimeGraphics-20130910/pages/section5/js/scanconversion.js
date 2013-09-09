
"use strict";

var scanConversionHTML = 
"<div id='scanConversionHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section5/img/scanconversion.png'></img>" +
"</div>";

function scanConversion_activate() {
	$("#dynamic_area").append(scanConversionHTML);
}

function scanConversion_deactivate() {
	$("#scanConversionHTML").remove();
}

function scanConversion_render() {
}

PowerPoint.append_page("Scanconversion", scanConversion_activate, scanConversion_deactivate, scanConversion_render);


"use strict";

var circleScanConversionHTML = 
"<div id='circleScanConversionHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section5/img/Circle_Scanconversion.png'></img>" +
"</div>";

function circleScanConversion_activate() {
	$("#dynamic_area").append(circleScanConversionHTML);
}

function circleScanConversion_deactivate() {
	$("#circleScanConversionHTML").remove();
}

function circleScanConversion_render() {
}

PowerPoint.append_page("Circle scanconversion", circleScanConversion_activate, circleScanConversion_deactivate, circleScanConversion_render);

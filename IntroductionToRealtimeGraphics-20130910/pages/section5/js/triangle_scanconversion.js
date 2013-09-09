
"use strict";

var triangleScanConversionHTML = 
"<div id='triangleScanConversionHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section5/img/Triangle_Scanconversion.png'></img>" +
"</div>";

function triangleScanConversion_activate() {
	$("#dynamic_area").append(triangleScanConversionHTML);
}

function triangleScanConversion_deactivate() {
	$("#triangleScanConversionHTML").remove();
}

function triangleScanConversion_render() {
}

PowerPoint.append_page("Triangle scanconversion", triangleScanConversion_activate, triangleScanConversion_deactivate, triangleScanConversion_render);

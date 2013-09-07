
"use strict";

var additiveColorMixingHTML = 
"<div id='additiveColorMixingHTML' class='container' style='text-align:center'>" +
"	<p></p>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p><h3>Primary colors: Red, Green, Blue</h3></p>" +
"			<p><h3>Mix them to create other colors</h3></p>" +
"		</div>" +
"		<div class='span6'>" +
"			<img src='images/rgb_color_mixing.png'></img>" +
"		</div>" +
"	</div>" +
"	<div class='row'>" +
"		<div class='span12' style='display:inline-block; height:50px'>" +
"	</div>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<table>" +
"				<tbody>" +
"					<tr>" +
"						<td>" +
"							<input type='text' value='' data-slider-min='0' data-slider-max='255' data-slider-step='1' data-slider-value='128' data-slider-id='RC' id='R' data-slider-tooltip='hide'>" +
"							<p id='Rvalue'></p>" +
"						</td>" +
"					</tr>" +
"					<tr>" +
"						<td>" +
"						<input type='text' value='' data-slider-min='0' data-slider-max='255' data-slider-step='1' data-slider-value='128' data-slider-id='GC' id='G' data-slider-tooltip='hide'>" +
"							<p id='Gvalue'></p>" +
"						</td>" +
"					</tr>" +
"					<tr>" +
"						<td>" +
"							<input type='text' value='' data-slider-min='0' data-slider-max='255' data-slider-step='1' data-slider-value='128' data-slider-id='BC' id='B' data-slider-tooltip='hide'>" +
"							<p id='Bvalue'></p>" +
"						</td>" +
"					</tr>" +
"				</tbody>" +
"			</table>" +
"		</div>" +
"		<div class='span6' id='coloredRegion' style='display:inline-block; height:200px'>" +
"		</div>" +
"	</div>" +
"</div>";

function additiveColorMixing_activate() {
	$("#dynamic_area").append(additiveColorMixingHTML);
	$("#R").slider();
	$("#G").slider();
	$("#B").slider();
}

function additiveColorMixing_deactivate() {
	$("#additiveColorMixingHTML").remove();
}

function decimalToHex(d, padding) {
    var hex = Number(d).toString(16);
    padding = typeof (padding) === "undefined" || padding === null ? padding = 2 : padding;

    while (hex.length < padding) {
        hex = "0" + hex;
    }

    return hex;
}
function additiveColorMixing_render() {
	
	var redColor = $("#R").data("slider").getValue();
	var greenColor = $("#G").data("slider").getValue();
	var blueColor = $("#B").data("slider").getValue();

	var hexColor = "#" + decimalToHex(redColor) + decimalToHex(greenColor) + decimalToHex(blueColor);

	$("#Rvalue").text("Red: " + redColor);
	$("#Gvalue").text("Green: " + greenColor);
	$("#Bvalue").text("Blue: " + blueColor);
	$("#coloredRegion").css({backgroundColor : hexColor});
}

PowerPoint.append_page("Additive color mixing", additiveColorMixing_activate, additiveColorMixing_deactivate, additiveColorMixing_render);


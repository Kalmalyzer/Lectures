
"use strict";

var section2HTML = 
"<div id='section2HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>Section 2<br><br>Pixel manipulation</h1></p></div>" +
"</div>";

function section2_activate() {
	$("#dynamic_area").append(section2HTML);
}

function section2_deactivate() {
	$("#section2HTML").remove();
}

function section2_render() {
}

PowerPoint.append_page("Section 2", section2_activate, section2_deactivate, section2_render);

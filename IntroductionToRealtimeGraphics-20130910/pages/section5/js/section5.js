
"use strict";

var section5HTML = 
"<div id='section5HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>Section 5<br><br>Improving performance</h1></p></div>" +
"</div>";

function section5_activate() {
	$("#dynamic_area").append(section5HTML);
}

function section5_deactivate() {
	$("#section5HTML").remove();
}

function section5_render() {
}

PowerPoint.append_page("Section 5", section5_activate, section5_deactivate, section5_render);

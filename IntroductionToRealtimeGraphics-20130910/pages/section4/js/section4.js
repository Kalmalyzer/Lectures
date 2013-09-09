
"use strict";

var section4HTML = 
"<div id='section4HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>Section 4<br><br>Rendering shapes</h1></p></div>" +
"</div>";

function section4_activate() {
	$("#dynamic_area").append(section4HTML);
}

function section4_deactivate() {
	$("#section4HTML").remove();
}

function section4_render() {
}

PowerPoint.append_page("Section 4", section4_activate, section4_deactivate, section4_render);

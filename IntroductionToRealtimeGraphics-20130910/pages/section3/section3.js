
"use strict";

var section3HTML = 
"<div id='section3HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>Section 3<br><br>Image bending</h1></p></div>" +
"</div>";

function section3_activate() {
	$("#dynamic_area").append(section3HTML);
}

function section3_deactivate() {
	$("#section3HTML").remove();
}

function section3_render() {
}

PowerPoint.append_page("Section 3", section3_activate, section3_deactivate, section3_render);

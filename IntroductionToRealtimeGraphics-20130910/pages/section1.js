
"use strict";

var section1HTML = 
"<div id='section1HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>Section 1<br><br>Images and displays</h1></p></div>" +
"</div>";

function section1_activate() {
	$("#dynamic_area").append(section1HTML);
}

function section1_deactivate() {
	$("#section1HTML").remove();
}

function section1_render() {
}

PowerPoint.append_page("Section 2", section1_activate, section1_deactivate, section1_render);

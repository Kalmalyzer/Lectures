
"use strict";

var section5HTML = 
"<div id='section5HTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:100px; margin-bottom:200px'><p><h1>The End.<br><br>Questions?</h1><br><br>mikael@kalms.org<br><br>Download this lecture: http://www.github.com/Kalmalyzer/Lectures</p></div>" +
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

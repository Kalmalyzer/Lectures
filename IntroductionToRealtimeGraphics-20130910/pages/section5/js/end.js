
"use strict";

var endHTML = 
"<div id='endHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:100px; margin-bottom:200px'><p><h1>The End.<br><br>Questions?</h1><br><br>mikael@kalms.org<br><br>Download this lecture: http://www.github.com/Kalmalyzer/Lectures</p></div>" +
"</div>";

function end_activate() {
	$("#dynamic_area").append(endHTML);
}

function end_deactivate() {
	$("#endHTML").remove();
}

function end_render() {
}

PowerPoint.append_page("The End", end_activate, end_deactivate, end_render);

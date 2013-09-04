
"use strict";

var welcomeHTML = 
"<div id='welcomeHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:50px;margin-bottom:50px'><p><h1>Pixel pushing bonanza</h1></p></div>" +
"	<p><h2>Mikael Kalms</h2></p>" +
"	<p>mikael@kalms.org</p>" +
"</div>";

function welcome_activate() {
	$("#dynamic_area").append(welcomeHTML);
}

function welcome_deactivate() {
	$("#welcomeHTML").remove();
}

function welcome_render() {
}

PowerPoint.append_page("Welcome", welcome_activate, welcome_deactivate, welcome_render);

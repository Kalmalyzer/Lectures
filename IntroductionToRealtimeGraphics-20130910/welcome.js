
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
	$("#dynamic_area").remove($("#welcomeHTML"));
}

function welcome_render() {
}

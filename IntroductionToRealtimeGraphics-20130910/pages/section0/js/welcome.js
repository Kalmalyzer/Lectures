
"use strict";

var welcomeHTML = 
"<div id='welcomeHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:50px;margin-bottom:50px'><p><h2>Realtime computer graphics - absolute basics</h2></p></div>" +
"	<p>" +
"		<h2>Mikael Kalms</h2><br>" +
"		mikael@kalms.org<br><br><br><br><br>" +
"		use space and arrow keys to navigate<br><br>" +
"		Viewing the HTML locally? Make sure your browser allows local file access, or else pictures won't load" +
"	</p>" +
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

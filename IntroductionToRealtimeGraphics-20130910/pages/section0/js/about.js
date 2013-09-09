
"use strict";

var aboutHTML = 
"<div id='aboutHTML' class='container'>" +
"	<div class='container' style='margin-top:50px;margin-bottom:50px'><p><h1>About this lecture</h1></p></div>" +
"   <p>We'll talk basic computer graphics</p>" +
"	<ul>" +
"		<li>Images and displays</li>" +
"		<li>Pixel manipulation</li>" +
"		<li>Image bending</li>" +
"		<li>Rendering shapes</li>" +
"		<li>Improving performance</li>" +
"	</ul>" +
"</div>";

function about_activate() {
	$("#dynamic_area").append(aboutHTML);
}

function about_deactivate() {
	$("#aboutHTML").remove();
}

function about_render() {
}

PowerPoint.append_page("About", about_activate, about_deactivate, about_render);


"use strict";

var aboutHTML = 
"<div id='aboutHTML' class='container'>" +
"	<div class='container' style='margin-top:50px;margin-bottom:50px'><p><h1>About this lecture</h1></p></div>" +
"   <p>We'll talk basic computer graphics</p>" +
"	<ul>" +
"		<li>displays</li>" +
"		<li>what's a pixel?</li>" +
"		<li>images</li>" +
"		<li>framebuffers & graphics cards</li>" +
"		<li>drawing shapes</li>" +
"		<li>choosing colors</li>" +
"		<li>connecting this to 3D hardware and maths</li>" +
"	</ul>" +
"</div>";

function about_activate() {
	$("#dynamic_area").append(aboutHTML);
}

function about_deactivate() {
	$("#dynamic_area").remove($("#aboutHTML"));
}

function about_render() {
}

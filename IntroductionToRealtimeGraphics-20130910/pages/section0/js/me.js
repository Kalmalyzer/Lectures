
"use strict";

var meHTML = 
"<div id='meHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/me.png'></img>" +
"</div>";

function me_activate() {
	$("#dynamic_area").append(meHTML);
}

function me_deactivate() {
	$("#meHTML").remove();
}

function me_render() {
}

PowerPoint.append_page("Me", me_activate, me_deactivate, me_render);


"use strict";

var oupsHTML = 
"<div id='oupsHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/oups.png'></img>" +
"</div>";

function oups_activate() {
	$("#dynamic_area").append(oupsHTML);
}

function oups_deactivate() {
	$("#oupsHTML").remove();
}

function oups_render() {
}

PowerPoint.append_page("Oups", oups_activate, oups_deactivate, oups_render);

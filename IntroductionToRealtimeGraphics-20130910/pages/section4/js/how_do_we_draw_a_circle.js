
"use strict";

var howDoWeDrawACircleHTML = 
"<div id='howDoWeDrawACircleHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h3>How do we draw a circle?</h3></p></div>" +
"</div>";

function howDoWeDrawACircle_activate() {
	$("#dynamic_area").append(howDoWeDrawACircleHTML);
}

function howDoWeDrawACircle_deactivate() {
	$("#howDoWeDrawACircleHTML").remove();
}

function howDoWeDrawACircle_render() {
}

PowerPoint.append_page("How do we draw a circle?", howDoWeDrawACircle_activate, howDoWeDrawACircle_deactivate, howDoWeDrawACircle_render);

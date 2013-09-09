
"use strict";

var triangleEquationSetHTML = 
"<div id='triangleEquationSetHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section4/img/Triangle_equation_set.png'></img>" +
"</div>";

function triangleEquationSet_activate() {
	$("#dynamic_area").append(triangleEquationSetHTML);
}

function triangleEquationSet_deactivate() {
	$("#triangleEquationSetHTML").remove();
}

function triangleEquationSet_render() {
}

PowerPoint.append_page("Triangle equation set", triangleEquationSet_activate, triangleEquationSet_deactivate, triangleEquationSet_render);

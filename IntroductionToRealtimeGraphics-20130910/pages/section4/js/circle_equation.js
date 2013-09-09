
"use strict";

var circleEquationHTML = 
"<div id='circleEquationHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section4/img/Circle_Equation.png'></img>" +
"</div>";

function circleEquation_activate() {
	$("#dynamic_area").append(circleEquationHTML);
}

function circleEquation_deactivate() {
	$("#circleEquationHTML").remove();
}

function circleEquation_render() {
}

PowerPoint.append_page("Circle equation", circleEquation_activate, circleEquation_deactivate, circleEquation_render);

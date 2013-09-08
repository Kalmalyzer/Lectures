
"use strict";

var halfSpaceEquationHTML = 
"<div id='halfSpaceEquationHTML' class='container' style='text-align:center'>" +
"	<img src='images/Halfspace_Equation.png'></img>" +
"</div>";

function halfSpaceEquation_activate() {
	$("#dynamic_area").append(halfSpaceEquationHTML);
}

function halfSpaceEquation_deactivate() {
	$("#halfSpaceEquationHTML").remove();
}

function halfSpaceEquation_render() {
}

PowerPoint.append_page("Halfspace equation", halfSpaceEquation_activate, halfSpaceEquation_deactivate, halfSpaceEquation_render);


"use strict";

var myFormativeYearsHTML = 
"<div id='myFormativeYearsHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_formative_years.png'></img>" +
"</div>";

function myFormativeYears_activate() {
	$("#dynamic_area").append(myFormativeYearsHTML);
}

function myFormativeYears_deactivate() {
	$("#myFormativeYearsHTML").remove();
}

function myFormativeYears_render() {
}

PowerPoint.append_page("My formative years", myFormativeYears_activate, myFormativeYears_deactivate, myFormativeYears_render);

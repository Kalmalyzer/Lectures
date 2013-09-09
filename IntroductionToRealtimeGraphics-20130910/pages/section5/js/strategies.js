
"use strict";

var strategiesHTML = 
"<div id='strategiesHTML' class='container' style='margin-top:100px; margin-left:100px'>" +
"	<h3>Strategies for improving performance</h3>" +
"	<ul>" +
"		<li>Change algorithm</li>" +
"		<li>Change language</li>" +
"		<li>Change hardware</li>" +
"		<li><b>Change your desired end result</b></li>" +
"	</ul>" +
"</div>";

function strategies_activate() {
	$("#dynamic_area").append(strategiesHTML);
}

function strategies_deactivate() {
	$("#strategiesHTML").remove();
}

function strategies_render() {
}

PowerPoint.append_page("Strategies for improving performance", strategies_activate, strategies_deactivate, strategies_render);

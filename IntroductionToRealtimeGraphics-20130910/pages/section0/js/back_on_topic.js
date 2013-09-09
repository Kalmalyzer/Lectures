
"use strict";

var backOnTopicHTML = 
"<div id='backOnTopicHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h1>But, back on topic.</h1></p></div>" +
"</div>";

function backOnTopic_activate() {
	$("#dynamic_area").append(backOnTopicHTML);
}

function backOnTopic_deactivate() {
	$("#backOnTopicHTML").remove();
}

function backOnTopic_render() {
}

PowerPoint.append_page("Anyway...", backOnTopic_activate, backOnTopic_deactivate, backOnTopic_render);


"use strict";

var gpuHTML = 
"<div id='gpuHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section5/img/gtx280_architecture.png'></img>" +
"</div>";

function gpu_activate() {
	$("#dynamic_area").append(gpuHTML);
}

function gpu_deactivate() {
	$("#gpuHTML").remove();
}

function gpu_render() {
}

PowerPoint.append_page("GPU architecture example", gpu_activate, gpu_deactivate, gpu_render);

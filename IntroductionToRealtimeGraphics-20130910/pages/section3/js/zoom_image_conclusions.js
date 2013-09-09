
"use strict";

var zoomImageConclusionsHTML = 
"<div id='zoomImageConclusionsHTML' class='container' style='text-align:center'>" +
"	<div class='container' style='margin-top:200px; margin-bottom:200px'><p><h3>Mapping dest-&gt;source is usually better when doing image manipulation!</h3></p></div>" +
"</div>";

function zoomImageConclusions_activate() {
	$("#dynamic_area").append(zoomImageConclusionsHTML);
}

function zoomImageConclusions_deactivate() {
	$("#zoomImageConclusionsHTML").remove();
}

function zoomImageConclusions_render() {
}

PowerPoint.append_page("Zoom image conclusions", zoomImageConclusions_activate, zoomImageConclusions_deactivate, zoomImageConclusions_render);

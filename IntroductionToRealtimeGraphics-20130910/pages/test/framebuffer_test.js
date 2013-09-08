
"use strict";

var testHTML = 
"<div id='testHTML' class='container' style='text-align:center'>" +
"	<div class='row'>" +
"		<div class='span4'>" +
"			<p><h3>Test</h3></p>" +
"		</div>" +
"		<div class='span8' id='canvas_parent'>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var test_frameBuffer;

function test_activate() {
	$("#dynamic_area").append(testHTML);

	var canvas = $("#canvas")[0];
	test_frameBuffer = new FrameBuffer(canvas);
}

function test_deactivate() {
	$("#testHTML").remove();
	test_frameBuffer = null;
}

function test_render() {

	test_frameBuffer.clear();
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 640; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			test_frameBuffer.drawPixel(x, y, color.r, color.g, color.b);
		}

	test_frameBuffer.update();
}

PowerPoint.append_page("Test", test_activate, test_deactivate, test_render);

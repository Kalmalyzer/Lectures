
"use strict";

var displayImageHTML = 
"<div id='displayImageHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Let's copy a loaded image into our framebuffer.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var color = src.readPixel(x, y);<br>" +
"    dest.drawPixel(x, y, color);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var displayImage_frameBuffer;

function displayImage_activate() {
	$("#dynamic_area").append(displayImageHTML);
	
	var canvas = $("#canvas")[0];
	displayImage_frameBuffer = new FrameBuffer(canvas);
}

function displayImage_deactivate() {
	$("#displayImageHTML").remove();
	displayImage_frameBuffer = null;
}

function displayImage_render() {

	displayImage_frameBuffer.clear();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			displayImage_frameBuffer.drawPixel(x, y, color);
		}

	displayImage_frameBuffer.update();
}

PowerPoint.append_page("Displaying an image", displayImage_activate, displayImage_deactivate, displayImage_render);

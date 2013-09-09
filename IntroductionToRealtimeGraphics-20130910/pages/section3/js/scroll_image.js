
"use strict";

var scrollImageHTML = 
"<div id='scrollImageHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Moving (scrolling) an image.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var color = src.readPixel(x, y);<br>" +
"    dest.drawPixel(x + offset, y, color);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> offset: 0 <input type='text' value='' data-slider-min='0' data-slider-max='600' data-slider-step='1' data-slider-value='1' id='offset'> 600 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var scrollImage_frameBuffer;

function scrollImage_activate() {
	$("#dynamic_area").append(scrollImageHTML);
	$("#offset").slider(); 
	
	var canvas = $("#canvas")[0];
	scrollImage_frameBuffer = new FrameBuffer(canvas);
}

function scrollImage_deactivate() {
	$("#scrollImageHTML").remove();
	scrollImage_frameBuffer = null;
}

function scrollImage_render() {

	scrollImage_frameBuffer.clear();

	var offset = $("#offset").data("slider").getValue();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			scrollImage_frameBuffer.drawPixel(x + offset, y, color);
		}

	scrollImage_frameBuffer.update();
}

PowerPoint.append_page("Scroll image", scrollImage_activate, scrollImage_deactivate, scrollImage_render);

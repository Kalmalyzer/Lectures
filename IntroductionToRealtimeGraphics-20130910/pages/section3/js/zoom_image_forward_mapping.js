
"use strict";

var zoomImageForwardMappingHTML = 
"<div id='zoomImageForwardMappingHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Zooming an image.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var color = src.readPixel(x, y);<br>" +
"    var destX = Math.floor(x * scale);<br>" +
"    var destY = Math.floor(y * scale);<br>" +
"    dest.drawPixel(destX, destY, color);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> scale: 0 <input type='text' value='' data-slider-min='0' data-slider-max='5' data-slider-step='0.01' data-slider-value='1' id='scale'> 5 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var zoomImageForwardMapping_frameBuffer;

function zoomImageForwardMapping_activate() {
	$("#dynamic_area").append(zoomImageForwardMappingHTML);
	$("#scale").slider(); 
	
	var canvas = $("#canvas")[0];
	zoomImageForwardMapping_frameBuffer = new FrameBuffer(canvas);
}

function zoomImageForwardMapping_deactivate() {
	$("#zoomImageForwardMappingHTML").remove();
	zoomImageForwardMapping_frameBuffer = null;
}

function zoomImageForwardMapping_render() {

	zoomImageForwardMapping_frameBuffer.clear();

	var scale = $("#scale").data("slider").getValue();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			var destX = Math.floor(x * scale);
			var destY = Math.floor(y * scale);
			zoomImageForwardMapping_frameBuffer.drawPixel(destX, destY, color);
		}

	zoomImageForwardMapping_frameBuffer.update();
}

PowerPoint.append_page("Zoom image (forward mapping)", zoomImageForwardMapping_activate, zoomImageForwardMapping_deactivate, zoomImageForwardMapping_render);


"use strict";

var zoomImageReverseMappingHTML = 
"<div id='zoomImageReverseMappingHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Zooming an image.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var srcX = Math.floor(x * scale);<br>" +
"    var srcY = Math.floor(y * scale);<br>" +
"    var color = src.readPixel(srcX, srcY);<br>" +
"    dest.drawPixel(x, y, color);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> scale: 0 <input type='text' value='' data-slider-min='0' data-slider-max='5' data-slider-step='0.01' data-slider-value='1' id='scale'> 5 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var zoomImageReverseMapping_frameBuffer;

function zoomImageReverseMapping_activate() {
	$("#dynamic_area").append(zoomImageReverseMappingHTML);
	$("#scale").slider(); 
	
	var canvas = $("#canvas")[0];
	zoomImageReverseMapping_frameBuffer = new FrameBuffer(canvas);
}

function zoomImageReverseMapping_deactivate() {
	$("#zoomImageReverseMappingHTML").remove();
	zoomImageReverseMapping_frameBuffer = null;
}

function zoomImageReverseMapping_render() {

	zoomImageReverseMapping_frameBuffer.clear();

	var scale = $("#scale").data("slider").getValue();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var srcX = Math.floor(x * scale);
			var srcY = Math.floor(y * scale);
			var color = globalTestImage.readPixel(srcX, srcY);
			zoomImageReverseMapping_frameBuffer.drawPixel(x, y, color);
		}

	zoomImageReverseMapping_frameBuffer.update();
}

PowerPoint.append_page("Zoom image (Reverse mapping)", zoomImageReverseMapping_activate, zoomImageReverseMapping_deactivate, zoomImageReverseMapping_render);

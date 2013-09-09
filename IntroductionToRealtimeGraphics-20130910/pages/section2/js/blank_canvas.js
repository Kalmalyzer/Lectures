
"use strict";

var blankCanvasHTML = 
"<div id='blankCanvasHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Let's start by drawing into a blank canvas.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    dest.drawPixel(x, y,<br>" +
"                   {r: value, g: value, b: value});<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> 0 <input type='text' value='' data-slider-min='0' data-slider-max='255' data-slider-step='1' data-slider-value='128' id='value'> 255 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var blankCanvas_frameBuffer;

function blankCanvas_activate() {
	$("#dynamic_area").append(blankCanvasHTML);
	$("#value").slider(); 
	
	var canvas = $("#canvas")[0];
	blankCanvas_frameBuffer = new FrameBuffer(canvas);
}

function blankCanvas_deactivate() {
	$("#blankCanvasHTML").remove();
	blankCanvas_frameBuffer = null;
}

function blankCanvas_render() {

	blankCanvas_frameBuffer.clear();

	var value = $("#value").data("slider").getValue();
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			blankCanvas_frameBuffer.drawPixel(x, y, {r: value, g: value, b: value});
		}

	blankCanvas_frameBuffer.update();
}

PowerPoint.append_page("Blank canvas", blankCanvas_activate, blankCanvas_deactivate, blankCanvas_render);

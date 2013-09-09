
"use strict";

var convertToGreyscaleHTML = 
"<div id='convertToGreyscaleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Converting a color image to greyscale.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var color = src.readPixel(x, y);<br>" +
"    var intensity = (color.r + color.g + color.b) / 3;<br>" +
"    <br>" +
"    var color2 =<br>" +
"      {<br>" +
"        r: intensity * value + color.r * (1 - value),<br>" +
"        g: intensity * value + color.g * (1 - value),<br>" +
"        b: intensity * value + color.b * (1 - value)<br>" +
"      };<br>" +
"    <br>" +
"    dest.drawPixel(x, y, color2);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> value: 0 <input type='text' value='' data-slider-min='0' data-slider-max='1' data-slider-step='0.01' data-slider-value='0.01' id='value'> 1.0 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var convertToGreyscale_frameBuffer;

function convertToGreyscale_activate() {
	$("#dynamic_area").append(convertToGreyscaleHTML);
	$("#value").slider(); 
	
	var canvas = $("#canvas")[0];
	convertToGreyscale_frameBuffer = new FrameBuffer(canvas);
}

function convertToGreyscale_deactivate() {
	$("#convertToGreyscaleHTML").remove();
	convertToGreyscale_frameBuffer = null;
}

function convertToGreyscale_render() {

	convertToGreyscale_frameBuffer.clear();

	var value = $("#value").data("slider").getValue();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			var intensity = (color.r + color.g + color.b) / 3;
			var color2 =
				{
					r: intensity * value + color.r * (1 - value),
					g: intensity * value + color.g * (1 - value),
					b: intensity * value + color.b * (1 - value)
				};
			convertToGreyscale_frameBuffer.drawPixel(x, y, color2);
		}

	convertToGreyscale_frameBuffer.update();
}

PowerPoint.append_page("Converting to greyscale", convertToGreyscale_activate, convertToGreyscale_deactivate, convertToGreyscale_render);


"use strict";

var modulateColorChannelsHTML = 
"<div id='modulateColorChannelsHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Modulation of R/G/B components independently.</p>" +

"<p><pre>" +
"for (var y = 0; y < 480; y++)<br>" +
"  for (var x = 0; x < 600; x++)<br>" +
"  {<br>" +
"    var color = src.readPixel(x, y);<br>" +
"    color.r *= rscale;<br>" +
"    color.g *= gscale;<br>" +
"    color.b *= bscale;<br>" +
"    dest.drawPixel(x, y, color);<br>" +
"  }<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> rscale: 0 <input type='text' value='' data-slider-min='0' data-slider-max='1' data-slider-step='0.01' data-slider-value='0.5' id='rscale'> 1.0 </div>" +
"			<div> gscale: 0 <input type='text' value='' data-slider-min='0' data-slider-max='1' data-slider-step='0.01' data-slider-value='0.5' id='gscale'> 1.0 </div>" +
"			<div> bscale: 0 <input type='text' value='' data-slider-min='0' data-slider-max='1' data-slider-step='0.01' data-slider-value='0.5' id='bscale'> 1.0 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var modulateColorChannels_frameBuffer;

function modulateColorChannels_activate() {
	$("#dynamic_area").append(modulateColorChannelsHTML);
	$("#rscale").slider(); 
	$("#gscale").slider(); 
	$("#bscale").slider(); 
	
	var canvas = $("#canvas")[0];
	modulateColorChannels_frameBuffer = new FrameBuffer(canvas);
}

function modulateColorChannels_deactivate() {
	$("#modulateColorChannelsHTML").remove();
	modulateColorChannels_frameBuffer = null;
}

function modulateColorChannels_render() {

	modulateColorChannels_frameBuffer.clear();

	var rscale = $("#rscale").data("slider").getValue();
	var gscale = $("#gscale").data("slider").getValue();
	var bscale = $("#bscale").data("slider").getValue();

	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color = globalTestImage.readPixel(x, y);
			color.r *= rscale;
			color.g *= gscale;
			color.b *= bscale;
			modulateColorChannels_frameBuffer.drawPixel(x, y, color);
		}

	modulateColorChannels_frameBuffer.update();
}

PowerPoint.append_page("Modulating color channels", modulateColorChannels_activate, modulateColorChannels_deactivate, modulateColorChannels_render);

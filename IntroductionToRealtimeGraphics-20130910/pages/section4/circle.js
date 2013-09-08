
"use strict";

var circleHTML = 
"<div id='circleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>TODO UPDATE</p>" +

"<p><pre>" +
"TODO UPDATE<br>" +
"</pre></p>" +

"		</div>" +
"		<div class='span6'>" +
"			<div> radius: 0 <input type='text' value='' data-slider-min='0' data-slider-max='200' data-slider-step='1' data-slider-value='100' id='radius'> 200 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var circle_frameBuffer;

function circle_activate() {
	$("#dynamic_area").append(circleHTML);
	$("#radius").slider(); 
	
	var canvas = $("#canvas")[0];
	circle_frameBuffer = new FrameBuffer(canvas);
}

function circle_deactivate() {
	$("#circleHTML").remove();
	circle_frameBuffer = null;
}

function circle_render() {

	circle_frameBuffer.clear();

	var radius = $("#radius").data("slider").getValue();

	var x0 = circle_frameBuffer.width / 2;
	var y0 = circle_frameBuffer.height / 2;
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var sqrDistance = (x - x0) * (x - x0) + (y - y0) * (y - y0);
			var color;
			if (sqrDistance < radius * radius)
				color = { r: 255, g: 255, b: 0};
			else
				color = { r: 0, g: 0, b: 0};
			
			circle_frameBuffer.drawPixel(x, y, color);
		}

	circle_frameBuffer.update();
}

PowerPoint.append_page("Circle", circle_activate, circle_deactivate, circle_render);

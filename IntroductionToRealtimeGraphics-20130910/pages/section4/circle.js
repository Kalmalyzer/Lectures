
"use strict";

var circleHTML = 
"<div id='circleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Drawing a circle, by in/out test for every pixel</p>" +

"<p><pre>" +
"function isInside(x, y) {<br>" +
"  var dx = x - x0;<br>" +
"  var dy = y - y0;<br>" +
"  var sqrDistance = dx * dx + dy * dy;<br>" +
"  if (sqrDistance &lt; radius * radius)<br>" +
"    return true;<br>" +
"  else<br>" +
"    return false;<br>" +
"}<br>" +
"<br>" +
"for (var y = 0; y &lt; 480; y++)<br>" +
"  for (var x = 0; x &lt; 600; x++)<br>" +
"  {<br>" +
"    var color;<br>" +
"    if (isInside(x, y))<br>" +
"      color = { r: 255, g: 255, b: 0};<br>" +
"    else<br>" +
"      color = { r: 0, g: 0, b: 0};<br>" +
"<br>" +
"    dest.drawPixel(x, y, color);<br>" +
"  }<br>" +
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

var circle_x0;
var circle_y0;
var circle_radius;

function circle_isInside(x, y) {
	var dx = x - circle_x0;
	var dy = y - circle_y0;
	var sqrDistance = dx * dx + dy * dy;
	if (sqrDistance < circle_radius * circle_radius)
		return true;
	else
		return false;
}

function circle_render() {

	circle_frameBuffer.clear();

	circle_x0 = circle_frameBuffer.width / 2;
	circle_y0 = circle_frameBuffer.height / 2;
	circle_radius = $("#radius").data("slider").getValue();
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color;
			if (circle_isInside(x, y))
				color = { r: 255, g: 255, b: 0};
			else
				color = { r: 0, g: 0, b: 0};
			
			circle_frameBuffer.drawPixel(x, y, color);
		}

	circle_frameBuffer.update();
}

PowerPoint.append_page("Circle", circle_activate, circle_deactivate, circle_render);

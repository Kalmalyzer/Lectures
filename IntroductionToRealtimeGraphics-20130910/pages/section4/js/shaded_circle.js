
"use strict";

var shadedCircleHTML = 
"<div id='shadedCircleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Drawing a circle, with computed gradient</p>" +

"<p><pre>" +
"function isInside(x, y) {<br>" +
"  var dx = x - x0;<br>" +
"  var dy = y - y0;<br>" +
"  var sqrDistance = dx * dx + dy * dy;<br>" +
"  return (sqrDistance &lt; radius * radius);<br>" +
"}</pre></p>" +
"<p><pre>function getColor(x, y) {<br>" +
"  var dx = x - x0;<br>" +
"  var dy = y - y0;<br>" +
"  var distance = Math.sqrt(dx * dx + dy * dy);<br>" +
"  var t = distance / radius;<br>" +
"  return { r: 255 * t, g: 255 * t, b: 0 };<br>" +
"}</pre></p>" +
"<p><pre>for (var y = 0; y &lt; 480; y++)<br>" +
"  for (var x = 0; x &lt; 600; x++)<br>" +
"  {<br>" +
"    var color;<br>" +
"    if (isInside(x, y))<br>" +
"      color = getColor(x, y);<br>" +
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

var shadedCircle_frameBuffer;

function shadedCircle_activate() {
	$("#dynamic_area").append(shadedCircleHTML);
	$("#radius").slider(); 
	
	var canvas = $("#canvas")[0];
	shadedCircle_frameBuffer = new FrameBuffer(canvas);
}

function shadedCircle_deactivate() {
	$("#shadedCircleHTML").remove();
	shadedCircle_frameBuffer = null;
}

var shadedCircle_x0;
var shadedCircle_y0;
var shadedCircle_radius;

function shadedCircle_isInside(x, y) {
	var dx = x - shadedCircle_x0;
	var dy = y - shadedCircle_y0;
	var sqrDistance = dx * dx + dy * dy;
	if (sqrDistance < shadedCircle_radius * shadedCircle_radius)
		return true;
	else
		return false;
}

function shadedCircle_getColor(x, y) {
	var dx = x - shadedCircle_x0;
	var dy = y - shadedCircle_y0;
	var distance = Math.sqrt(dx * dx + dy * dy);
	var t = distance / shadedCircle_radius;
	
	return { r: 255 * t, g: 255 * t, b: 0 };
}

function shadedCircle_render() {

	shadedCircle_frameBuffer.clear();

	shadedCircle_x0 = shadedCircle_frameBuffer.width / 2;
	shadedCircle_y0 = shadedCircle_frameBuffer.height / 2;
	shadedCircle_radius = $("#radius").data("slider").getValue();
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color;
			if (shadedCircle_isInside(x, y))
				color = shadedCircle_getColor(x, y);
			else
				color = { r: 0, g: 0, b: 0};
			
			shadedCircle_frameBuffer.drawPixel(x, y, color);
		}

	shadedCircle_frameBuffer.update();
}

PowerPoint.append_page("Shaded circle", shadedCircle_activate, shadedCircle_deactivate, shadedCircle_render);

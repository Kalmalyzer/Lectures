
"use strict";

var triangleHTML = 
"<div id='triangleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Drawing a triangle, by in/out test for every pixel</p>" +

"<p><pre>" +
"function halfSpace.isInside(x, y) {<br>" +
"	return x * this.a + y * this.b + this.c > 0;<br>" +
"}<br>" +
"<br>" +
"function isInside(x, y) {<br>" +
"	return halfSpace0.isInside(x, y)<br>" +
"		&& halfSpace1.isInside(x, y)<br>" +
"		&& halfSpace2.isInside(x, y);<br>" +
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
"			<div><input id='testHalfSpace0' type='checkbox' value='1'>Test first halfspace</input></div>" +
"			<div><input id='testHalfSpace1' type='checkbox' value='1'>Test second halfspace</input></div>" +
"			<div><input id='testHalfSpace2' type='checkbox' value='1'>Test third halfspace</input></div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var triangle_frameBuffer;

function triangle_activate() {
	$("#dynamic_area").append(triangleHTML);
	
	var canvas = $("#canvas")[0];
	triangle_frameBuffer = new FrameBuffer(canvas);
}

function triangle_deactivate() {
	$("#triangleHTML").remove();
	triangle_frameBuffer = null;
}

var triangle_halfSpace0;
var triangle_halfSpace1;
var triangle_halfSpace2;

var triangle_testHalfSpace0;
var triangle_testHalfSpace1;
var triangle_testHalfSpace2;

function triangle_createHalfSpace(x0, y0, x1, y1) {
	var dx = x1 - x0;
	var dy = y1 - y0;
	var a = -dy;
	var b = dx;
	var c = -(x0 * a + y0 * b);
	return { a: a, b: b, c: c };
}

function triangle_isInsideHalfSpace(halfSpace, x, y) {
	return x * halfSpace.a + y * halfSpace.b + halfSpace.c > 0;
}

function triangle_isInsideTriangle(x, y) {
	return (!triangle_testHalfSpace0 || triangle_isInsideHalfSpace(triangle_halfSpace0, x, y))
		&& (!triangle_testHalfSpace1 || triangle_isInsideHalfSpace(triangle_halfSpace1, x, y))
		&& (!triangle_testHalfSpace2 || triangle_isInsideHalfSpace(triangle_halfSpace2, x, y));
}

function triangle_render() {

	triangle_frameBuffer.clear();

	var x0 = 180;
	var y0 = 50;
	var x1 = 500;
	var y1 = 200;
	var x2 = 50;
	var y2 = 350;
	
	triangle_halfSpace0 = triangle_createHalfSpace(x0, y0, x1, y1);
	triangle_halfSpace1 = triangle_createHalfSpace(x1, y1, x2, y2);
	triangle_halfSpace2 = triangle_createHalfSpace(x2, y2, x0, y0);

	triangle_testHalfSpace0 = $("#testHalfSpace0").prop('checked');
	triangle_testHalfSpace1 = $("#testHalfSpace1").prop('checked');
	triangle_testHalfSpace2 = $("#testHalfSpace2").prop('checked');
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color;
			if (triangle_isInsideTriangle(x, y))
				color = { r: 255, g: 255, b: 0};
			else
				color = { r: 0, g: 0, b: 0};
			
			triangle_frameBuffer.drawPixel(x, y, color);
		}

	triangle_frameBuffer.update();
}

PowerPoint.append_page("Triangle", triangle_activate, triangle_deactivate, triangle_render);

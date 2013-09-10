
"use strict";

var shadedTriangleHTML = 
"<div id='shadedTriangleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Drawing a triangle, with a gradient</p>" +

"<p><pre>" +
"function halfSpace.isInside(x, y) {<br>" +
"	return x * this.a + y * this.b + this.c > 0;<br>" +
"}<br>" +
"<br>" +
"function isInside(x, y) {<br>" +
"	return halfSpace0.isInside(x, y)<br>" +
"		&& halfSpace1.isInside(x, y)<br>" +
"		&& halfSpace2.isInside(x, y);<br>" +
"}</p></pre>" +
"<p><pre>" +
"function getColor(x, y) {<br>" +
"	var r = rGradient.gradient(x, y);<br>" +
"	var g = gGradient.gradient(x, y);<br>" +
"	var b = bGradient.gradient(x, y);<br>" +
"  return { r: r, g: g, b: b };<br>" +
"}</pre></p>" +
"<p><pre>" +
"for (var y = 0; y &lt; 480; y++)<br>" +
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
"			<div><input id='testHalfSpace0' type='checkbox' value='1'>Test first halfspace</input></div>" +
"			<div><input id='testHalfSpace1' type='checkbox' value='1'>Test second halfspace</input></div>" +
"			<div><input id='testHalfSpace2' type='checkbox' value='1'>Test third halfspace</input></div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var shadedTriangle_frameBuffer;

function shadedTriangle_activate() {
	$("#dynamic_area").append(shadedTriangleHTML);
	
	var canvas = $("#canvas")[0];
	shadedTriangle_frameBuffer = new FrameBuffer(canvas);
}

function shadedTriangle_deactivate() {
	$("#shadedTriangleHTML").remove();
	shadedTriangle_frameBuffer = null;
}

var shadedTriangle_halfSpace0;
var shadedTriangle_halfSpace1;
var shadedTriangle_halfSpace2;

var shadedTriangle_testHalfSpace0;
var shadedTriangle_testHalfSpace1;
var shadedTriangle_testHalfSpace2;

var shadedTriangle_colorGradient;

function shadedTriangle_createHalfSpace(x0, y0, x1, y1) {
	var dx = x1 - x0;
	var dy = y1 - y0;
	var a = -dy;
	var b = dx;
	var c = -(x0 * a + y0 * b);
	return { a: a, b: b, c: c };
}

function shadedTriangle_isInsideHalfSpace(halfSpace, x, y) {
	return x * halfSpace.a + y * halfSpace.b + halfSpace.c > 0;
}

function shadedTriangle_isInsideTriangle(x, y) {
	return (!shadedTriangle_testHalfSpace0 || shadedTriangle_isInsideHalfSpace(shadedTriangle_halfSpace0, x, y))
		&& (!shadedTriangle_testHalfSpace1 || shadedTriangle_isInsideHalfSpace(shadedTriangle_halfSpace1, x, y))
		&& (!shadedTriangle_testHalfSpace2 || shadedTriangle_isInsideHalfSpace(shadedTriangle_halfSpace2, x, y));
}

function shadedTriangle_colorChannelGradient(gradient, x, y) {
	return x * gradient.dcdx + y * gradient.dcdy + gradient.c00;
}

function shadedTriangle_getColor(x, y) {
	var r = shadedTriangle_colorChannelGradient(shadedTriangle_colorGradient.rGradient, x, y);
	var g = shadedTriangle_colorChannelGradient(shadedTriangle_colorGradient.gGradient, x, y);
	var b = shadedTriangle_colorChannelGradient(shadedTriangle_colorGradient.bGradient, x, y);
	return { r: r, g: g, b: b };
}

function shadedTriangle_computeChannelGradient(inverseDenom, x0, y0, dx01, dx02, dy01, dy02, c0, c1, c2) {
	var dc01 = c1 - c0;
	var dc02 = c2 - c0;

	var dcdx = (dc01 * dy02 - dc02 * dy01) * inverseDenom;
	var dcdy = (dc02 * dx01 - dc01 * dx02) * inverseDenom;
	var c00 = c0 -(x0 * dcdx + y0 * dcdy);
	
	return { dcdx: dcdx, dcdy: dcdy, c00: c00 };
}

function shadedTriangle_computeGradient(p0, p1, p2) {
	var dx01 = p1.x - p0.x;
	var dx02 = p2.x - p0.x;
	var dy01 = p1.y - p0.y;
	var dy02 = p2.y - p0.y;
	
	var denom = dx01 * dy02 - dx02 * dy01;
	var inverseDenom = 1 / denom;

	var rGradient = shadedTriangle_computeChannelGradient(inverseDenom, p0.x, p0.y, dx01, dx02, dy01, dy02, p0.color.r, p1.color.r, p2.color.r);
	var gGradient = shadedTriangle_computeChannelGradient(inverseDenom, p0.x, p0.y, dx01, dx02, dy01, dy02, p0.color.g, p1.color.g, p2.color.g);
	var bGradient = shadedTriangle_computeChannelGradient(inverseDenom, p0.x, p0.y, dx01, dx02, dy01, dy02, p0.color.b, p1.color.b, p2.color.b);

	return { rGradient: rGradient, gGradient: gGradient, bGradient: bGradient };
}

function shadedTriangle_render() {

	shadedTriangle_frameBuffer.clear();

	var x0 = 180;
	var y0 = 50;
	var color0 = { r: 255, g: 0, b: 0 };

	var x1 = 500;
	var y1 = 200;
	var color1 = { r: 0, g: 255, b: 0 };
	
	var x2 = 50;
	var y2 = 350;
	var color2 = { r: 0, g: 0, b: 255 };
	
	shadedTriangle_halfSpace0 = shadedTriangle_createHalfSpace(x0, y0, x1, y1);
	shadedTriangle_halfSpace1 = shadedTriangle_createHalfSpace(x1, y1, x2, y2);
	shadedTriangle_halfSpace2 = shadedTriangle_createHalfSpace(x2, y2, x0, y0);

	shadedTriangle_colorGradient = shadedTriangle_computeGradient({x: x0, y: y0, color: color0}, {x: x1, y: y1, color: color1}, {x: x2, y: y2, color: color2});
	
	shadedTriangle_testHalfSpace0 = $("#testHalfSpace0").prop('checked');
	shadedTriangle_testHalfSpace1 = $("#testHalfSpace1").prop('checked');
	shadedTriangle_testHalfSpace2 = $("#testHalfSpace2").prop('checked');
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color;
			if (shadedTriangle_isInsideTriangle(x, y))
				color = shadedTriangle_getColor(x, y);
			else
				color = { r: 0, g: 0, b: 0};
			
			shadedTriangle_frameBuffer.drawPixel(x, y, color);
		}

	shadedTriangle_frameBuffer.update();
}

PowerPoint.append_page("Triangle", shadedTriangle_activate, shadedTriangle_deactivate, shadedTriangle_render);

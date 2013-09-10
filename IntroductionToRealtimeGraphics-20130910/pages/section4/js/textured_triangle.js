
"use strict";

var texturedTriangleHTML = 
"<div id='texturedTriangleHTML' class='container'>" +
"	<div class='row'>" +
"		<div class='span6'>" +
"			<p>Drawing a triangle, with a texture</p>" +

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
"	var u = Math.floor(uGradient.gradient(x, y));<br>" +
"	var v = Math.floor(vGradient.gradient(x, y));<br>" +
"  return srcImage.readPixel(u, v);<br>" +
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
"			<div> angle: 0 <input type='text' value='' data-slider-min='0' data-slider-max='360' data-slider-step='1' data-slider-value='1' id='angle'> 360 </div>" +
"			<canvas id='canvas' width='640' height='480'></canvas>" +
"		</div>" +
"	</div>" +
"</div>";

var texturedTriangle_frameBuffer;

function texturedTriangle_activate() {
	$("#dynamic_area").append(texturedTriangleHTML);
	$("#angle").slider();

	var canvas = $("#canvas")[0];
	texturedTriangle_frameBuffer = new FrameBuffer(canvas);
}

function texturedTriangle_deactivate() {
	$("#texturedTriangleHTML").remove();
	texturedTriangle_frameBuffer = null;
}

var texturedTriangle_halfSpace0;
var texturedTriangle_halfSpace1;
var texturedTriangle_halfSpace2;

var texturedTriangle_testHalfSpace0;
var texturedTriangle_testHalfSpace1;
var texturedTriangle_testHalfSpace2;

var texturedTriangle_textureGradient;

function texturedTriangle_createHalfSpace(x0, y0, x1, y1) {
	var dx = x1 - x0;
	var dy = y1 - y0;
	var a = -dy;
	var b = dx;
	var c = -(x0 * a + y0 * b);
	return { a: a, b: b, c: c };
}

function texturedTriangle_isInsideHalfSpace(halfSpace, x, y) {
	return x * halfSpace.a + y * halfSpace.b + halfSpace.c > 0;
}

function texturedTriangle_isInsideTriangle(x, y) {
	return (!texturedTriangle_testHalfSpace0 || texturedTriangle_isInsideHalfSpace(texturedTriangle_halfSpace0, x, y))
		&& (!texturedTriangle_testHalfSpace1 || texturedTriangle_isInsideHalfSpace(texturedTriangle_halfSpace1, x, y))
		&& (!texturedTriangle_testHalfSpace2 || texturedTriangle_isInsideHalfSpace(texturedTriangle_halfSpace2, x, y));
}

function texturedTriangle_channelGradient(gradient, x, y) {
	return x * gradient.dcdx + y * gradient.dcdy + gradient.c00;
}

function texturedTriangle_getColor(x, y) {
	var u = texturedTriangle_channelGradient(texturedTriangle_textureGradient.uGradient, x, y);
	var v = texturedTriangle_channelGradient(texturedTriangle_textureGradient.vGradient, x, y);
	var color = globalTestImage.readPixel(Math.floor(u), Math.floor(v));
	return color;
}

function texturedTriangle_computeChannelGradient(inverseDenom, x0, y0, dx01, dx02, dy01, dy02, c0, c1, c2) {
	var dc01 = c1 - c0;
	var dc02 = c2 - c0;

	var dcdx = (dc01 * dy02 - dc02 * dy01) * inverseDenom;
	var dcdy = (dc02 * dx01 - dc01 * dx02) * inverseDenom;
	var c00 = c0 -(x0 * dcdx + y0 * dcdy);
	
	return { dcdx: dcdx, dcdy: dcdy, c00: c00 };
}

function texturedTriangle_computeGradient(p0, p1, p2) {
	var dx01 = p1.x - p0.x;
	var dx02 = p2.x - p0.x;
	var dy01 = p1.y - p0.y;
	var dy02 = p2.y - p0.y;
	
	var denom = dx01 * dy02 - dx02 * dy01;
	var inverseDenom = 1 / denom;

	var uGradient = texturedTriangle_computeChannelGradient(inverseDenom, p0.x, p0.y, dx01, dx02, dy01, dy02, p0.uv.u, p1.uv.u, p2.uv.u);
	var vGradient = texturedTriangle_computeChannelGradient(inverseDenom, p0.x, p0.y, dx01, dx02, dy01, dy02, p0.uv.v, p1.uv.v, p2.uv.v);

	return { uGradient: uGradient, vGradient: vGradient };
}

function rotate(x, y, xCenter, yCenter, angle) {
	var ca = Math.cos(angle);
	var sa = Math.sin(angle);

	var x0 = x - xCenter;
	var y0 = y - yCenter;

	var x1 = x0 * ca - y0 * sa;
	var y1 = x0 * sa + y0 * ca;
	
	var x2 = x1 + xCenter;
	var y2 = y1 + yCenter;
	
	return { x: x2, y: y2 };
}

function texturedTriangle_render() {

	texturedTriangle_frameBuffer.clear();

	var x0 = 180;
	var y0 = 50;
	var uv0 = { u: 100, v: 100 };

	var x1 = 500;
	var y1 = 200;
	var uv1 = { u: 250, v: 100 };
	
	var x2 = 50;
	var y2 = 350;
	var uv2 = { u: 100, v: 250 };

	var xCenter = 300;
	var yCenter = 240;

	var angle = $("#angle").data("slider").getValue() * 3.141592 * 2 / 360; 	

	var xy0 = rotate(x0, y0, xCenter, yCenter, angle);
	x0 = xy0.x;
	y0 = xy0.y;

	var xy1 = rotate(x1, y1, xCenter, yCenter, angle);
	x1 = xy1.x;
	y1 = xy1.y;

	var xy2 = rotate(x2, y2, xCenter, yCenter, angle);
	x2 = xy2.x;
	y2 = xy2.y;
	
	texturedTriangle_halfSpace0 = texturedTriangle_createHalfSpace(x0, y0, x1, y1);
	texturedTriangle_halfSpace1 = texturedTriangle_createHalfSpace(x1, y1, x2, y2);
	texturedTriangle_halfSpace2 = texturedTriangle_createHalfSpace(x2, y2, x0, y0);

	texturedTriangle_textureGradient = texturedTriangle_computeGradient({x: x0, y: y0, uv: uv0}, {x: x1, y: y1, uv: uv1}, {x: x2, y: y2, uv: uv2});
	
	texturedTriangle_testHalfSpace0 = $("#testHalfSpace0").prop('checked');
	texturedTriangle_testHalfSpace1 = $("#testHalfSpace1").prop('checked');
	texturedTriangle_testHalfSpace2 = $("#testHalfSpace2").prop('checked');
	
	for (var y = 0; y < 480; y++)
		for (var x = 0; x < 600; x++)
		{
			var color;
			if (texturedTriangle_isInsideTriangle(x, y))
				color = texturedTriangle_getColor(x, y);
			else
				color = { r: 0, g: 0, b: 0};
			
			texturedTriangle_frameBuffer.drawPixel(x, y, color);
		}

	texturedTriangle_frameBuffer.update();
}

PowerPoint.append_page("Textured Triangle", texturedTriangle_activate, texturedTriangle_deactivate, texturedTriangle_render);


"use strict";

var displayHTML = 
"<div id='displayHTML' class='container' style='text-align:center'>" +
"	<p>An LCD display</p>" +
"	<div id='renderTarget'></div>" +
"</div>";

var renderer = new THREE.WebGLRenderer();

var camera = new THREE.PerspectiveCamera( 60, 1, 1, 10000 );
camera.position.z = 50;

var geometry = new THREE.CubeGeometry(30, 30, 30);
var texture = new THREE.Texture( createImage() );
texture.needsUpdate = true;
var material = new THREE.MeshBasicMaterial( { map: texture } );

var scene = new THREE.Scene();
var mesh = new THREE.Mesh( geometry, material );
scene.add( mesh );

function display_activate() {
	$("#dynamic_area").append(displayHTML);
	$("#displayHTML").append( renderer.domElement );
}

function display_deactivate() {
	$("#displayHTML").remove();
}

function createImage() {

	var canvas = document.createElement( 'canvas' );
	canvas.width = 256;
	canvas.height = 256;

	var context = canvas.getContext( '2d' );
	context.fillStyle = 'rgb(255,255,0)';
	context.fillRect( 0, 0, 256, 256 );

	return canvas;
}

function display_render() {

	var renderTargetElement = $("#renderTarget");

	var renderTargetWidth = renderTargetElement.innerWidth();
	var renderTargetHeight = window.innerHeight - renderTargetElement.offset().top;

	camera.aspect = renderTargetWidth / renderTargetHeight;
	camera.updateProjectionMatrix(); 
	renderer.setSize( renderTargetWidth, renderTargetHeight );

	renderer.render( scene, camera );
}

PowerPoint.append_page("Display", display_activate, display_deactivate, display_render);


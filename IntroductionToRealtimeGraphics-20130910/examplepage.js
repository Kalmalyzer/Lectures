
"use strict";

function examplepage_init() {

	container = document.createElement( 'div' );
	document.body.appendChild( container );

	camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 10000 );
	camera.position.z = 200;

	scene = new THREE.Scene();

	renderer = new THREE.WebGLRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight );
	container.appendChild( renderer.domElement );

}

function createImage() {

	var canvas = document.createElement( 'canvas' );
	canvas.width = 256;
	canvas.height = 256;

	var context = canvas.getContext( '2d' );
	context.fillStyle = 'rgb(' + Math.floor( Math.random() * 256 ) + ',' + Math.floor( Math.random() * 256 ) + ',' + Math.floor( Math.random() * 256 ) + ')';
	context.fillRect( 0, 0, 256, 256 );

	return canvas;

}

function examplepage_render() {

	$("#main_header").clone().appendTo("#main_header");

	var geometry = new THREE.SphereGeometry( 50, Math.random() * 64, Math.random() * 32 );

	var texture = new THREE.Texture( createImage() );
	texture.needsUpdate = true;

	var material = new THREE.MeshBasicMaterial( { map: texture, wireframe: true } )

	var mesh = new THREE.Mesh( geometry, material );

	scene.add( mesh );

	renderer.render( scene, camera );

	scene.remove( mesh );

	// clean up

	geometry.dispose();
	material.dispose();
	texture.dispose();

}

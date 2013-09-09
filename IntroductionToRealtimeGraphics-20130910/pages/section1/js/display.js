
"use strict";

var displayHTML = 
"<div id='displayHTML' class='container' style='text-align:center'>" +
"	<p>An LCD display</p>" +
"   <div ><input class='span6' id='slider' data-slider-min='0' data-slider-max='1' data-slider-step='0.001' data-slider-value='0.01' data-slider-tooltip='hide'></div>" +
"	<div id='renderTarget'></div>" +
"</div>";
// 
var renderer = new THREE.WebGLRenderer();

var camera = new THREE.PerspectiveCamera( 60, 1, 1, 10000 );
camera.position.z = 50;

var geometry = new THREE.PlaneGeometry(80, 50);
var texture = THREE.ImageUtils.loadTexture( "pages/section1/img/monitor.jpg" );
var material = new THREE.MeshBasicMaterial( { map: texture } );

var scene = new THREE.Scene();
var mesh = new THREE.Mesh( geometry, material );

var pixels_layer_materials = new Array();

for (var i = 0; i < 5; i++)
{
	var pixels_layer_texture = THREE.ImageUtils.loadTexture("pages/section1/img/pixels_layer" + i + ".png");
	pixels_layer_texture.repeat.set(400, 400);
	pixels_layer_texture.wrapS = THREE.RepeatWrapping;
	pixels_layer_texture.wrapT = THREE.RepeatWrapping;

	var pixels_layer_geometry = new THREE.PlaneGeometry(80, 80);

	var pixels_layer_material = new THREE.MeshBasicMaterial( { map: pixels_layer_texture, transparent: true } );
	var pixels_layer_mesh = new THREE.Mesh(pixels_layer_geometry, pixels_layer_material);
	scene.add(pixels_layer_mesh);
	pixels_layer_materials.push(pixels_layer_material);
}

scene.add( mesh );


function display_activate() {
	$("#dynamic_area").append(displayHTML);
	$("#displayHTML").append( renderer.domElement );
	$("#slider").slider();
}

function display_deactivate() {
	$("#displayHTML").remove();
}

function computeOpacities(sliderPosition) {
	var fadeStart = 0.8;
	sliderPosition = (sliderPosition - fadeStart) / (1 - fadeStart);

	for (var i = 0; i < pixels_layer_materials.length; i++)
	{
		var center = i / pixels_layer_materials.length;
		var delta = 1 / pixels_layer_materials.length;

		var t = Math.max(Math.min((sliderPosition - center) / delta, 1), 0);
		pixels_layer_materials[i].opacity = t;
	}
}

function display_render() {

	var renderTargetElement = $("#renderTarget");

	var renderTargetWidth = renderTargetElement.innerWidth();
	var renderTargetHeight = window.innerHeight - renderTargetElement.offset().top;

	var sliderPosition = $("#slider").data("slider").getValue();
	
	computeOpacities(sliderPosition);
	
	camera.aspect = renderTargetWidth / renderTargetHeight;
	camera.position.z = 50 - 49 * sliderPosition;
	camera.updateProjectionMatrix(); 
	renderer.setSize( renderTargetWidth, renderTargetHeight );
	
	renderer.render( scene, camera );
}

PowerPoint.append_page("Display", display_activate, display_deactivate, display_render);


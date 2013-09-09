
"use strict";

var changing_hardwareHTML = 
"<div id='changing_hardwareHTML' class='container' style='margin-top:200px; text-align:center'>" +
"	<p>" +
"		<h3>JavaScript and C++ runs on the CPU. What about the GPU?</h3><br><br>" +
"		<h3>More performance, but you need to structure your code differently.</h3><br><br>" +
"		<h3>Or ... use 3D acceleration APIs</h3>" +
"	</p>" +
"</div>";

function changing_hardware_activate() {
	$("#dynamic_area").append(changing_hardwareHTML);
}

function changing_hardware_deactivate() {
	$("#changing_hardwareHTML").remove();
}

function changing_hardware_render() {
}

PowerPoint.append_page("Changing hardware", changing_hardware_activate, changing_hardware_deactivate, changing_hardware_render);

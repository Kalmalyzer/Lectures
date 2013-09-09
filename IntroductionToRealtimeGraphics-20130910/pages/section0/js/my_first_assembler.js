
"use strict";

var myMachineOfChoiceHTML = 
"<div id='myMachineOfChoiceHTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_machine_of_choice.png'></img>" +
"</div>";

function myMachineOfChoice_activate() {
	$("#dynamic_area").append(myMachineOfChoiceHTML);
}

function myMachineOfChoice_deactivate() {
	$("#myMachineOfChoiceHTML").remove();
}

function myMachineOfChoice_render() {
}

PowerPoint.append_page("My machine of choice", myMachineOfChoice_activate, myMachineOfChoice_deactivate, myMachineOfChoice_render);


"use strict";

var my_games_2HTML = 
"<div id='my_games_2HTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_games_2.png'></img>" +
"</div>";

function my_games_2_activate() {
	$("#dynamic_area").append(my_games_2HTML);
}

function my_games_2_deactivate() {
	$("#my_games_2HTML").remove();
}

function my_games_2_render() {
}

PowerPoint.append_page("My games (2)", my_games_2_activate, my_games_2_deactivate, my_games_2_render);


"use strict";

var my_games_3HTML = 
"<div id='my_games_3HTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_games_3.png'></img>" +
"</div>";

function my_games_3_activate() {
	$("#dynamic_area").append(my_games_3HTML);
}

function my_games_3_deactivate() {
	$("#my_games_3HTML").remove();
}

function my_games_3_render() {
}

PowerPoint.append_page("My games (3)", my_games_3_activate, my_games_3_deactivate, my_games_3_render);

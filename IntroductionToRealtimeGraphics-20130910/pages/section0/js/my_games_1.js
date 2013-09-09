
"use strict";

var my_games_1HTML = 
"<div id='my_games_1HTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_games_1.png'></img>" +
"</div>";

function my_games_1_activate() {
	$("#dynamic_area").append(my_games_1HTML);
}

function my_games_1_deactivate() {
	$("#my_games_1HTML").remove();
}

function my_games_1_render() {
}

PowerPoint.append_page("My games (1)", my_games_1_activate, my_games_1_deactivate, my_games_1_render);

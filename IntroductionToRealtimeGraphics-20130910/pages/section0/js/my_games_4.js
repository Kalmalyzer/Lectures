
"use strict";

var my_games_4HTML = 
"<div id='my_games_4HTML' class='container' style='text-align:center'>" +
"	<img src='pages/section0/img/my_games_4.png'></img>" +
"</div>";

function my_games_4_activate() {
	$("#dynamic_area").append(my_games_4HTML);
}

function my_games_4_deactivate() {
	$("#my_games_4HTML").remove();
}

function my_games_4_render() {
}

PowerPoint.append_page("My games (4)", my_games_4_activate, my_games_4_deactivate, my_games_4_render);

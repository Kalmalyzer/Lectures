
"use strict";

var changing_languageHTML = 
"<div id='changing_languageHTML' class='container' style='margin-top:200px; text-align:center'>" +
"	<p>" +
"		<h3>This was Javascript. How about C++?</h3><br><br>" +
"		<h3>Better performance, but it takes longer to write working code.</h3>" +
"	</p>" +
"</div>";

function changing_language_activate() {
	$("#dynamic_area").append(changing_languageHTML);
}

function changing_language_deactivate() {
	$("#changing_languageHTML").remove();
}

function changing_language_render() {
}

PowerPoint.append_page("Changing language", changing_language_activate, changing_language_deactivate, changing_language_render);

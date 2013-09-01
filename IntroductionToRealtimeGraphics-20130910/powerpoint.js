
"use strict";

var PowerPoint = {};

PowerPoint.pages = [];
PowerPoint.currentPage = -1;
PowerPoint.desiredPage = 0;


PowerPoint.append_page = function(description, activateFunc, deactivateFunc, animateFunc) {
		PowerPoint.pages.push({ "description" : description,
			"activateFunc" : activateFunc,
			"deactivateFunc" : deactivateFunc,
			"animateFunc" : animateFunc });
};

PowerPoint.run = function () {
	requestAnimationFrame(PowerPoint.run);

	if (PowerPoint.currentPage != PowerPoint.desiredPage)
	{
		if (PowerPoint.currentPage != -1)
			PowerPoint.pages[PowerPoint.currentPage].deactivateFunc();

		if (PowerPoint.desiredPage != -1)
			PowerPoint.pages[PowerPoint.desiredPage].activateFunc();
		
		PowerPoint.currentPage = PowerPoint.desiredPage;
	}
	
	var page = PowerPoint.pages[PowerPoint.currentPage];

	$("#main_header").text(page.description);
	page.animateFunc();
};

PowerPoint.nextPage = function () {
	PowerPoint.desiredPage = (PowerPoint.desiredPage + 1) % PowerPoint.pages.length;
}

PowerPoint.handleKeyPress = function (event) {

	event = event || window.event;
	
	var keyCode = event.charCode || event.keyCode;
	
	if (keyCode == 32)
		PowerPoint.nextPage();
}

document.onkeydown=PowerPoint.handleKeyPress;


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

	if (PowerPoint.pages.length != 0)
	{
		if (PowerPoint.currentPage != PowerPoint.desiredPage)
		{
			if (PowerPoint.currentPage != -1)
				PowerPoint.pages[PowerPoint.currentPage].deactivateFunc();

			if (PowerPoint.desiredPage != -1)
				PowerPoint.pages[PowerPoint.desiredPage].activateFunc();
			
			PowerPoint.currentPage = PowerPoint.desiredPage;
		}

		var page = PowerPoint.pages[PowerPoint.currentPage];

		$("#page_name").text(page.description);
		$("#page_id").text("Page " + (PowerPoint.currentPage + 1) + " of " + PowerPoint.pages.length);
		page.animateFunc();
	}
	else
	{
		$("#page_name").text("No pages registered");
		$("#page_id").text("");
	}
};

PowerPoint.previousPage = function () {
	PowerPoint.desiredPage = (PowerPoint.desiredPage + PowerPoint.pages.length - 1) % PowerPoint.pages.length;
}

PowerPoint.nextPage = function () {
	PowerPoint.desiredPage = (PowerPoint.desiredPage + 1) % PowerPoint.pages.length;
}

PowerPoint.handleKeyPress = function (event) {

	event = event || window.event;
	
	var keyCode = event.charCode || event.keyCode;
	
	// Left arrow == previous page
	if (keyCode == 37)
		PowerPoint.previousPage();
	// Right arrow or Space == next page
	if (keyCode == 39 || keyCode == 32)
		PowerPoint.nextPage();
}

document.onkeydown=PowerPoint.handleKeyPress;


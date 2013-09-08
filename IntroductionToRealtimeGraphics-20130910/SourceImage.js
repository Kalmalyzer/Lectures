
"use strict";

function SourceImage(url) {

	this.image = new Image();

	var sourceImage = this;
	
	this.image.onload = function() {
		var canvas = document.createElement('canvas');
		canvas.width = sourceImage.image.width;
		canvas.height = sourceImage.image.height;

		var context = canvas.getContext('2d');
		context.drawImage(sourceImage.image, 0, 0 );

		var imageData = context.getImageData(0, 0, sourceImage.image.width, sourceImage.image.height);
		sourceImage.data = imageData.data;
		sourceImage.width = imageData.width;
		sourceImage.height = imageData.height;
	}
	
	this.image.src = url;

	
	this.readPixel = function(x, y) {
		if (x >= 0 && x < this.width && y >= 0 && y <= this.height) {
			var offset = ((y * this.width) + x) * 4;
			
			var r = this.data[offset + 0];
			var g = this.data[offset + 1];
			var b = this.data[offset + 2];

			return { r : r, g : g, b : b };
		}
		else {
			return { r : 0, g : 0, b : 0 };
		}
	}
}

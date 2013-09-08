
"use strict";

function FrameBuffer(canvas) {
	this.canvas = canvas;
	this.context = this.canvas.getContext('2d');
	this.width = this.canvas.width;
	this.height = this.canvas.height;
	this.imageData = this.context.createImageData(this.width, this.height);
	this.data = this.imageData.data;

	this.clear = function() {
		for (var i = 0, length = this.data.length; i < length; i++ ) {
			this.data[i] = 0xff;
		}
	}

	this.drawPixel = function(x, y, r, g, b) {
		if (x >= 0 && x < this.width && y >= 0 && y <= this.height) {
			var offset = ((y * this.width) + x) * 4;
			
			this.data[offset + 0] = r;
			this.data[offset + 1] = g;
			this.data[offset + 2] = b;
		}
	}

	this.update = function() {
		this.context.putImageData( this.imageData, 0, 0 );
	}
}

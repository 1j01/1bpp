
var canvascontainer = document.getElementById("zoom-container");
var canvas = document.getElementById("zoom");
var imgs = document.getElementsByTagName("img");

var ctx = canvas.getContext("2d");

window.onresize = setCanvas;

(
	canvascontainer.onclick = 
	canvascontainer.ontouchstart =
	canvas.onclick =
	canvas.ontouchstart =
		hidecanvas
)(
);;;//

for(img in imgs){
	imgs[img].onclick = function(){
		zoom(this,2);
		showcanvas();
	}
}

function hidecanvas(){
	canvascontainer.style.opacity = 0;
	canvas.style.top = "100px";
	canvascontainer.style.pointerEvents = "none";
}
function showcanvas(){
	var canvascontainer = document.getElementById("zoom-container");
	var canvas = document.getElementById("zoom");
	canvascontainer.style.opacity = 1;
	canvas.style.top = "50px";
	canvascontainer.style.pointerEvents = "all";
	setCanvas();
}
function setCanvas(){
	var cw = canvascontainer.clientWidth;
	var ch = canvascontainer.clientHeight;
	canvas.style.left = (cw-canvas.width)/2 + "px";
	canvas.style.top = (ch-canvas.height)/2 + "px";
}

function zoom(img, scale){
	// Create an offscreen canvas, draw an image to it, and fetch the pixels
	var canvas = document.getElementById("zoom");
	var offcv = canvas;
	var w = img.width;
	var h = img.height;
	offcv.width = h;
	offcv.height = w;
	var offtx = offcv.getContext('2d');
	offtx.drawImage(img, 0, 0);
	var imgData = offtx.getImageData(0, 0, w, h).data;
	
	// Draw the zoomed-up pixels to a different canvas context
	canvas.width = w * scale;
	canvas.height = h * scale;
	
	for (var x = 0; x < w; x++){
		for (var y = 0; y < h; y++){
			// Find the starting index in the one-dimensional image data
			//var i = (y*img.width + x)*4;ctx.fillStyle = "rgba("+imgData[i]+","+imgData[i+1]+","+imgData[i+2]+","+(imgData[i+3]/255)+")";
			ctx.fillStyle = (imgData[(y*w + x)*4+1]>128)?"white":"black";
			ctx.fillRect(x*scale, y*scale, scale, scale);
		}
	}
}


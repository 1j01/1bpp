
var imgs = document.getElementsByTagName("img");

var overlay = document.body.appendChild(document.createElement("div"));
var canvas = overlay.appendChild(document.createElement("canvas"));
overlay.id = "overlay";

var ctx = canvas.getContext("2d");

window.onresize = position_overlay_canvas;

(
	overlay.onclick = 
	overlay.ontouchstart =
	canvas.onclick =
	canvas.ontouchstart =
		hide_overlay
)(
);;;//

for(img in imgs){
	imgs[img].onclick = function(){
		zoom(this, 2);
		show_overlay();
	};
}

function hide_overlay(){
	overlay.style.opacity = 0;
	canvas.style.top = "100px";
	overlay.style.pointerEvents = "none";
}
function show_overlay(){
	overlay.style.opacity = 1;
	canvas.style.top = "50px";
	overlay.style.pointerEvents = "all";
	position_overlay_canvas();
}
function position_overlay_canvas(){
	var cw = overlay.clientWidth;
	var ch = overlay.clientHeight;
	canvas.style.left = (cw-canvas.width)/2 + "px";
	canvas.style.top = (ch-canvas.height)/2 + "px";
}

function zoom(img, scale){
	var w = img.width;
	var h = img.height;
	canvas.width = w * scale;
	canvas.height = h * scale;
	ctx.imageSmoothingEnabled = false;
	ctx.mozImageSmoothingEnabled = false;
	ctx.webkitImageSmoothingEnabled = false;
	ctx.drawImage(
		// source (image)
		img, 0, 0, w, h,
		// destination (on canvas)
		0, 0, w * scale, h * scale
	);
}



imgs = document.getElementsByTagName("img")

overlay = document.body.appendChild(document.createElement("div"))
canvas = overlay.appendChild(document.createElement("canvas"))
overlay.id = "overlay"

ctx = canvas.getContext("2d")


hide_overlay = ->
	overlay.style.opacity = 0
	overlay.style.pointerEvents = "none"
	canvas.style.top = "100px"

show_overlay = ->
	overlay.style.opacity = 1
	overlay.style.pointerEvents = "all"
	canvas.style.top = "50px"
	position_overlay_canvas()

position_overlay_canvas = ->
	canvas.style.left = "#{(overlay.clientWidth - canvas.width) / 2}px"
	canvas.style.top = "#{(overlay.clientHeight - canvas.height) / 2}px"

zoom = (img, scale)->
	canvas.width = img.width * scale
	canvas.height = img.height * scale
	ctx.imageSmoothingEnabled = off
	ctx.mozImageSmoothingEnabled = off
	ctx.webkitImageSmoothingEnabled = off
	ctx.drawImage(
		# source (image)
		img, 0, 0, img.width, img.height,
		# destination (on canvas)
		0, 0, canvas.width, canvas.height
	)


for img in imgs
	do (img)->
		img.style.cursor = "pointer"
		img.onclick = ->
			zoom(img, 2)
			show_overlay()

do (
	overlay.onclick = 
	overlay.ontouchstart =
	canvas.onclick =
	canvas.ontouchstart =
		hide_overlay
)

window.onresize = position_overlay_canvas


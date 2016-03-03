
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

showing_img = null
zoom_scale = 2

position_overlay_canvas = ->
	canvas.style.left = "#{(overlay.clientWidth - canvas.width) / 2}px"
	canvas.style.top = "#{(overlay.clientHeight - canvas.height) / 2}px"

show_img_zoomed = (img)->
	unless img instanceof HTMLImageElement
		hide_overlay()
		showing_img = null
		return
	canvas.width = img.width * zoom_scale
	canvas.height = img.height * zoom_scale
	ctx.imageSmoothingEnabled = off
	ctx.mozImageSmoothingEnabled = off
	ctx.webkitImageSmoothingEnabled = off
	ctx.drawImage(
		# source (image)
		img, 0, 0, img.width, img.height,
		# destination (on canvas)
		0, 0, canvas.width, canvas.height
	)
	showing_img = img
	show_overlay()


for img in imgs
	do (img)->
		img.style.cursor = "pointer"
		img.onclick = ->
			show_img_zoomed(img)

do (
	overlay.onclick = 
	overlay.ontouchstart =
	canvas.onclick =
	canvas.ontouchstart =
		hide_overlay
)

window.addEventListener "resize", position_overlay_canvas

window.addEventListener "keydown", (e)->
	switch e.keyCode
		when 39 # right
			# go forwards
			if showing_img
				show_img_zoomed(showing_img.nextElementSibling)
			else
				show_img_zoomed(document.querySelector("img:first-of-type"))
		when 37 # left
			# go backwards
			if showing_img
				show_img_zoomed(showing_img.previousElementSibling)
			else
				show_img_zoomed(document.querySelector("img:last-of-type"))
		when 27 # escape
			# close overlay
			hide_overlay()

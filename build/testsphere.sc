scene {
	width		600
	height		600
	bg			test.exr
	bgtype		cylindrical		
}

shape {
	type		sphere
	center		0 0 0
	radius		1.5
	shader		diffuse
}

camera {
	type		pinhole
	position	-3 0 2
	lookat		0 0 0
	up			0 0 -1
}

light {
	type		point
	position	-4 2 1
}
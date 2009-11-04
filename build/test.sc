scene {
	width		1200
	height		1200
	bg			test.exr
	bgtype		cylindrical		
}

shape {
	type		mesh
	file		../data/ajax.trkd
	shader		diffuse
}

camera {
	type		pinhole
	position	-3 0 2
	lookat		0 0 1.7
	up			0 0 -1
}

light {
	type		point
	position	-4 2 1
}
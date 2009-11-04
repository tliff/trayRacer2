scene {
	width		100
	height		100
	bg			test.exr
	bgtype		cylindrical		
}

shape {
	type		mesh
	file		../data/ajax5k.trkd
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
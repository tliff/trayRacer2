image {
  resolution 800 600
  aa 0 2
  filter gaussian
}

trace-depths {
  diff 4
  refl 3
  refr 2
}

photons {
  caustics 1000000 kd 100 0.5
}


gi {
  type igi
  samples 64         
  sets 1             
  b 0.00003          
  bias-samples 0     
}

shader {
  name debug_caustics
  type view-caustics
}

shader {
  name debug_globals
  type view-global
}

shader {
  name debug_gi
  type view-irradiance
}

camera {
  type pinhole
  eye    0 -205 50
  target 0 0 50
  up     0 0 1
  fov    45
  aspect 1.333333
}

shader {
  name Grey
  type diffuse
  diff 0.7 0.7 0.7
}

shader {
  name Blue
  type diffuse
  diff 0.25 0.25 0.8
}

shader {
  name Red
  type diffuse
  diff 0.8 0.25 0.25
}

shader {
  name Mirror
  type mirror
  refl 0.7 0.7 0.7
}

shader {
  name Glass
  type glass
  eta 1.6
  color 1 1 1
}

object {
  shader none
  type cornellbox
  corner0 -60 -60 0
  corner1  60  60 100
  left    0.80 0.25 0.25
  right   0.25 0.25 0.80
  top     0.70 0.70 0.70
  bottom  0.70 0.70 0.70
  back    0.70 0.70 0.70
  emit    15 15 15
  samples 32
}

object {
  shader Mirror
  type sphere
  c -30 30 20
  r 20
}

object {
  shader Glass
  type sphere
  c 28 2 20
  r 20
}

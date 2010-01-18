require 'trayracer'
WIDTH = 800
HEIGHT = 600


scene = Trayracer::Scene.new
scene.addShape(Trayracer::Sphere.new(Trayracer::Vector3.new(10,10,10), 1))

light = Trayracer::Light.new(Trayracer::Vector3.new(3,2,0))
scene.addLight(light)

camera = Trayracer::CameraPinhole.new
camera.setUp( Trayracer::Vector3.new(0,0,0), 
              Trayracer::Vector3.new(10,10,10), 
              Trayracer::Vector3.new(0,1,0),
              0.1*Math::PI,
              0.1*Math::PI)

renderer = Trayracer::RendererDefault.new

surface = Trayracer::RGBSurface.new(WIDTH, HEIGHT)

observer = Trayracer::RenderObserverConsole.new
renderer.addObserver(observer);

renderer.render(scene, camera, surface)



writer = Trayracer::ImageWriterTGA.new
tonemapper = Trayracer::ScalingToneMapper.new
outsurface = Trayracer::RGBSurface.new(WIDTH,HEIGHT)
tonemapper.map(surface,outsurface)

f = File.open('out.tga', 'w+')
f.write(writer.encode(outsurface))
f.close
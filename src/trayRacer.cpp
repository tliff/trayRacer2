//standard headers
#include <iostream>
#include <fstream>


#include "pluginmanager.hpp"

#include "sceneloader.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "rendersurface.hpp"
#include "renderobserver.hpp"

//include the tonemappers
#include "tonemapper.hpp"
#include "scalingtonemapper.hpp"

#include "imagewriter.hpp"
#include "imagereader.hpp"


#include "sampler.hpp"


//boost
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <stdlib.h>
#include <time.h>




using namespace trayRacer;

int main(int argc, const char* argv[])
{
	srand(time(NULL));

	//create a timer, used for statistics
	boost::timer timer;

	PluginManager::getInstance().loadPlugins();

	//check the command line

	//find the action we got

	//assume we want to render a scene

	std::cout << "Initializing SceneLoader...";
	SceneLoader* sceneLoader = dynamic_cast<SceneLoader*> ( CREATE_PLUGIN_INSTANCE ( "sceneloader", "sffile" ) );
	assert ( sceneLoader );
	std::cout << " done" << std::endl;
	std::cout << "Time running " << timer.elapsed() << "s" << std::endl;
	std::cout << "Loading scene...";
	Scene* scene = new Scene();
	sceneLoader->loadSceneFromFile ( scene, "test.sc" );
	assert ( scene );
	std::cout << " done" << std::endl;
	std::cout << "Time running " << timer.elapsed() << "s... resetting" << std::endl;
	timer.restart();
	std::cout << "Initializing Renderer...";
	Renderer* renderer =
	    dynamic_cast<Renderer*> ( CREATE_PLUGIN_INSTANCE ( "renderer", "default" ) );
	assert ( renderer );
	std::cout << " done" << std::endl;
	std::cout << "Creating Camera...";
	Camera* camera = NULL;
	
	//create a defaultcamera in case we have none
	if(!(camera = scene->getCamera())){
		std::cout << "No camera specified" << std::endl;
	    camera = dynamic_cast<Camera*> ( CREATE_PLUGIN_INSTANCE ( "camera", "pinhole" ) );
		camera->setUp(Vector3(0,0,500), Vector3(0,0,0), Vector3(0,1,0),0.1*M_PI, 0.1*M_PI);
	}
	assert ( camera );
	std::cout << "done" << std::endl;

	int width=600, height=600;
	if(scene->getProperty("width") != "") 
		width = boost::lexical_cast<int>(scene->getProperty("width"));
	if(scene->getProperty("height") != "")
	 	height = boost::lexical_cast<int>(scene->getProperty("height"));
	

// 	RenderObserver* ptObserver = 
// 		dynamic_cast<RenderObserver*> ( CREATE_PLUGIN_INSTANCE ( "renderobserver", "pixeltoaster" ) );
	RenderSurface* renderSurface = new RenderSurface ( width, height);

	RenderObserver* consoleObserver = 
		dynamic_cast<RenderObserver*> ( CREATE_PLUGIN_INSTANCE ( "renderobserver", "console" ) );
	renderer->addObserver(consoleObserver);
	
	RenderObserver* consoleObserverPT = 
		dynamic_cast<RenderObserver*> ( CREATE_PLUGIN_INSTANCE ( "renderobserver", "pixeltoaster" ) );
	renderer->addObserver(consoleObserverPT);
	
	renderer->render ( scene, camera, renderSurface );
	
	//std::cout << *camera << std::endl;

	
	std::cout << "Creating an ImageWriter...";
	ImageWriter* imageWriter =
	    dynamic_cast<ImageWriter*> ( CREATE_PLUGIN_INSTANCE ( "imagewriter", "tga" ) );
		assert ( imageWriter );
	std::cout << " done" << std::endl;

	ToneMapper* toneMapper = new ScalingToneMapper();

	RGBSurface* outputSurface = new RGBSurface ( width, height );
	std::cout << "Tonemapping the image...";
	toneMapper->map ( renderSurface, outputSurface );
	std::cout << " done" << std::endl;
	std::cout << "Wrinting image... ";
	std::ofstream imageStream("out.tga", std::ios::out | std::ios::binary);
	imageWriter->write (imageStream, outputSurface );
	imageStream.close();
	std::cout << " done" << std::endl;

	std::cout << "SUMMARY:" << std::endl;
	std::cout << "Time rendering " << timer.elapsed() << "s" << std::endl;
}


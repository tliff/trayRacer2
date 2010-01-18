
#include <shapes.hpp>
#include <light.hpp>
#include "sceneloader_test.hpp"
#include "shader.hpp"
#include "normalshader.hpp"
#include "diffuseshader.hpp"

bool SceneLoaderTest::loadSceneFromFile(Scene* scene, std::string filename){
 	Shader* myShader = new NormalShader();
	myShader = new DiffuseShader();

	Shape* myShape = new Mesh("../data/dragon.trkd");
//	std::cout << myShape->getBBox();
	myShape->setShader(myShader);
	scene->addShape(myShape);
	scene->addLight(new Light(Vector3(0,0,500)));
	return true;
}

//TRAYRACER_PLUGIN_EXPORT("sceneloader", "test", SceneLoaderTest);

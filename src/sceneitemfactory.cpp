#include "sceneitemfactory.hpp"
#include "normalshader.hpp"
#include "diffuseshader.hpp"
#include "sphere.hpp"

Camera* SceneItemFactory::camera(std::multimap<std::string,std::string> m){

	std::string type = "pinhole";
	
	std::multimap<std::string,std::string>::iterator result = m.find("type");
	if(result != m.end())
		type = result->second;
	Camera* camera =
	    dynamic_cast<Camera*> ( CREATE_PLUGIN_INSTANCE ( "camera", type ) );
	camera->setUp(m);
	return camera;
}

Shape* SceneItemFactory::shape(std::multimap<std::string,std::string> m){
	Shape* shape=NULL;
	std::string type;
	std::multimap<std::string,std::string>::iterator result = m.find("type");
	if(result != m.end())
		type = result->second;
	
	if(type == "mesh"){
		shape = new MeshKD();
		shape->setUp(m);
	}
	else if(type == "sphere"){
		shape = new Sphere();
		shape->setUp(m);
	}
	else{
		std::cerr << "UNABLE TO CREATE SHAPE "<< type << std::endl;
	}	
	result = m.find("shader");
	if(result != m.end()){
		if(result->second == "normal")
			shape->setShader(new NormalShader());
		if(result->second == "diffuse")
			shape->setShader(new DiffuseShader());
	}
	return shape;
}

Light* SceneItemFactory::light(std::multimap<std::string,std::string> m){
	Light* light=NULL;
	std::string type;
	std::multimap<std::string,std::string>::iterator result = m.find("type");
	if(result != m.end())
		type = result->second;
	
	if(type == "point"){
		light = new Light();
		light->setUp(m);
	}
	else{
		std::cerr << "UNABLE TO CREATE SHAPE "<< type << std::endl;
	}	
	return light;
	
}
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <map>
#include <fstream>
#include "shape.hpp"
#include "light.hpp"
#include "sceneitemfactory.hpp"
#include "imagereader.hpp"
#include "rgbsurface.hpp"

struct blockComparator
{
  bool operator()(std::string a, std::string b) const
  {
    return getValue(a) < getValue(b);
  }

  int getValue(std::string a) const{
	if(a == "scene")
		return 0;
	if(a == "camera")
		return 1;
	if(a == "shader")
		return 2;
	if(a == "shape")
		return 3;
  }
};


class Scene {
public: //FIXME
	std::vector<Shape*> shapeList;
	std::vector<Light*> lightList;
	Camera* camera;
	RGBSurface background;
	std::string backgroundType;

public:
	
	Scene(){
		camera = NULL;
	}
	void addShape(Shape* shape){
		shapeList.push_back(shape);
	}
	
	void addLight(Light* light){
		lightList.push_back(light);
	}

	bool getIntersection(const Ray &r, Intersection* i) 
	{
		for(std::vector<Shape*>::iterator it = shapeList.begin();
		  it != shapeList.end();
		  it++){
			(*it)->intersect(r, i);
		}
		if(i->distance != INFINITY)
			return true;
		return false;
	}
	
	Camera* getCamera(){
		return camera;
	}
	
	std::string getProperty(std::string key){
		std::multimap<std::string, std::string>::iterator it = sceneProperties.find(key);
		if(it == sceneProperties.end() )
			return "";
		else
			return it->second;
	}
	
	bool canSee(Vector3 const &a, Vector3 const &b) 
	{
		Vector3 direction(b-a);
		float distance = direction.getLength();
		direction.normalize();
		distance+=0.0001;
		Intersection i;
		i.distance = distance;
		Ray ray(a+direction*0.00005, direction);
		for(std::vector<Shape*>::iterator it = shapeList.begin();
		  it != shapeList.end();
		  it++){
			(*it)->intersect(ray, &i);
			if(i.distance < distance){
				return false;
			}
		}
		return true;
	}

	std::multimap<std::string, std::multimap<std::string,std::string>, blockComparator > properties;

	std::multimap<std::string, std::multimap<std::string,std::string> >::iterator lastBlock;
	
	std::multimap<std::string, std::string> sceneProperties;

	std::string lastArgument;


	void sceneBuilderNewBlock(std::string n){
		std::multimap<std::string,std::string> foo;
		lastBlock = properties.insert(std::pair<std::string, std::multimap<std::string,std::string> >(n, foo));
	}

	void sceneBuilderNewArgument(std::string n){
		lastArgument = n;
	}

	void sceneBuilderNewArgumentValue(std::string n){
		lastBlock->second.insert(std::pair<std::string, std::string>(lastArgument, n));
	}

	void dump(){
		for(std::multimap<std::string, std::multimap<std::string,std::string> >::iterator it = properties.begin();
		it != properties.end();
		++it){
			std::cout << it->first << std::endl;
			for(std::multimap<std::string,std::string>::iterator jt = it->second.begin();
			jt != it->second.end();
			++jt){
				std::cout << "\t" <<jt->first << "="<< jt->second <<std::endl; 
			}
		}
	}

	void create(){
		for(std::multimap<std::string, std::multimap<std::string,std::string> >::iterator it = properties.begin();
		it != properties.end();
		++it){

			if(it->first == "scene"){
				sceneProperties = it->second;
			}
			else if(it->first == "shader"){
				//FIXME
				//std::cout << "shader" << std::endl;
				//this->shaderFactory->build(it->second);
			}
			else if(it->first == "camera"){
				this->camera = SceneItemFactory::camera(it->second);
			}
			else if(it->first == "shape"){
				addShape(SceneItemFactory::shape(it->second));
			}
			else if(it->first == "light"){
				addLight(SceneItemFactory::light(it->second));
			}
		}
		checkSceneProperties();
	}

	Color getBackground(Vector3 n){
		Vector3 polar = n.getPolar();
		float phi = polar.y;
		float theta = polar.z;
		int x = (background.getWidth() * (phi/(2*M_PI)+M_PI));
		x %= background.getWidth();
		int y = (background.getHeight() * (theta/M_PI));
		y %= background.getHeight();
		//std::cout << polar << "  " << x << ":" << y << std::endl;
		return background.getPixel(x,y);
	/*	if(y < background.getHeight()/2)
			return Color(255,255,255);*/
		return Color(255,255,0);
	}

	void checkSceneProperties(){
		if(getProperty("bg") != ""){
			std::ifstream picStream(getProperty("bg").c_str(), std::ios::in | std::ios::binary);
			ImageReader* imageReader = dynamic_cast<ImageReader*> ( CREATE_PLUGIN_INSTANCE ( "imagereader", "exr" ) );
			imageReader->read(picStream, &background);
			delete imageReader;
			picStream.close();
		}
		if(getProperty("bgtype") != ""){
			if(getProperty("bgtype") == "cylindrical"){
				backgroundType = "cylindrical";
			}
		}
		
	}

};

#endif

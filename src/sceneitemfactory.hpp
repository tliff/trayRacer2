#ifndef __SCENEITEMFACTORY__
#define __SCENEITEMFACTORY__

#include <map>
#include <string>

#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "meshkd.hpp"
#include "pluginmanager.hpp"



class SceneItemFactory
{
public:
	static Camera* camera(std::multimap<std::string,std::string >  m);
	static Shape* shape(std::multimap<std::string,std::string >  m);
	static Light* light(std::multimap<std::string,std::string >  m);
private:
	SceneItemFactory ();
	virtual ~SceneItemFactory ();
	/* data */
};


#endif /* __SCENEITEMFACTORY__ */

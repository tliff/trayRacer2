#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "intersection.hpp"
#include "color.hpp"

class Scene;

class Intersection;
class Shader  {
protected:
	std::string name;
public:
    Shader();

    virtual ~Shader();
    
    virtual Color getRadiance(Scene* scene, Intersection *i)=0;
    
    std::string getName();

};

#endif

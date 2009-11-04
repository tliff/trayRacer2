#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "outputable.hpp"
#include "intersection.hpp"
#include "color.hpp"

class Scene;

class Intersection;
class Shader : public Outputable {
protected:
	std::string name;
public:
    Shader();

    virtual ~Shader();
    
    virtual Color getRadiance(Scene* scene, Intersection *i)=0;
    
    virtual std::string str() const{
    	return name;
    }
    std::string getName();

};

#endif

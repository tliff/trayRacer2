#ifndef DIFFUSESHADER_HPP
#define DIFFUSESHADER_HPP

#include <scene.hpp>
#include <shader.hpp>


/**
	@author tliff <tliff@laptop>
*/
class DiffuseShader : public Shader
{
public:
    DiffuseShader(){
    	this->name = "diffuse";
    }

    virtual Color getRadiance(Scene* scene, Intersection *i);

    ~DiffuseShader();

};

#endif

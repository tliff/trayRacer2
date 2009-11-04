#include "shader.hpp"
#include  "scene.hpp"

    Shader::Shader(){
    name="BASESHADER";
    }

Shader::~Shader(){}

/*!
    \fn Shader::getName
 */
std::string Shader::getName()
{
return name;
}

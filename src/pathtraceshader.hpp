#ifndef __PATHTRACESHADER_H
#define __PATHTRACESHADER_H

#include "shader.hpp"

class PathtraceShader : public Shader {
public:
    PathtraceShader();

    ~PathtraceShader();
    
    Color getRadiance(Scene* scene, Intersection *i);

};

#endif

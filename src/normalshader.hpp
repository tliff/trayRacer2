//
// C++ Interface: normalshader
//
// Description: 
//
//
// Author: tliff <tliff@laptop>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NORMALSHADER_H
#define NORMALSHADER_H


#include "shader.hpp"

/**
	@author tliff <tliff@laptop>
*/
class NormalShader : public Shader {
public:
    NormalShader();

    ~NormalShader();
    
    Color getRadiance(Scene* scene, Intersection *i);

};

#endif

//
// C++ Implementation: normalshader
//
// Description: 
//
//
// Author: tliff <tliff@laptop>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "normalshader.hpp"
#include <iostream>

NormalShader::NormalShader()
{
	name="normal";
}


NormalShader::~NormalShader()
{
}


Color NormalShader::getRadiance(Scene* scene, Intersection *i){
        float r = (i->normal.x + 1) * 0.5f;
        float g = (i->normal.y + 1) * 0.5f;
        float b = (i->normal.z + 1) * 0.5f;
		return Color(r,g,b);
}

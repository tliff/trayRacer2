#include "pathtraceshader.hpp"
#include <iostream>

PathtraceShader::PathtraceShader()
{
	name="pathtrace";
}


PathtraceShader::~PathtraceShader()
{
}


Color PathtraceShader::getRadiance(Scene* scene, Intersection *i){
	Color c;
	for(int i = 0; i < 100; i++){
		
	}
}

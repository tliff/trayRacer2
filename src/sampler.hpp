#ifndef __SAMPLER_HPP
#define __SAMPLER_HPP

#include "math/matrix44.hpp"
#include "vector3.hpp"

class Sampler {
public:
	static Vector3 randomHemisphere(Vector3 n, float e=0.0){
		float cos_phi = cos(2*M_PI * randf());
		float sin_phi = sin(2*M_PI * randf());
		float cos_theta = pow(1.0-randf(),1.0/(e+1));
		float sin_theta = sqrt(1.0-cos_theta*cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
				
		Vector3 tmp(pu,pv,pw);
		Matrix44 tmpm = Matrix44::rotation(n);
		return tmpm*tmp;
	
	}
	
	static float randf(){
		return ((float)rand()/(float)RAND_MAX);
	}
};




#endif
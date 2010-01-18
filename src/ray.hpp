#ifndef __RAY__
#define __RAY__

#include "vector3.hpp"
#include <iostream>

class Ray  {
public:
  Vector3 origin, direction;
  Ray(const Vector3 &_origin, const Vector3 &_direction) : origin(_origin),
					     direction(_direction){};
  Ray() : origin ( Vector3(0,0,0)), direction (Vector3(0,0,1)){};  
  
};

#endif

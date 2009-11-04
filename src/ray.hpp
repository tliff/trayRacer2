#ifndef __RAY__
#define __RAY__

#include "vector3.hpp"
#include "outputable.hpp"
#include <iostream>

class Ray : public Outputable {
public:
  Vector3 origin, direction;
  Ray(const Vector3 &_origin, const Vector3 &_direction) : origin(_origin),
					     direction(_direction){};
  Ray() : origin ( Vector3(0,0,0)), direction (Vector3(0,0,1)){};  
  inline std::string str() const {
    std::stringstream ss;
    ss << "(" << origin.str() << direction.str() << ")";
    return ss.str();
  }
  
};

#endif

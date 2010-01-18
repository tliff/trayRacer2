#ifndef __INTERSECTION__
#define __INTERSECTION__

#include <sstream>
#include "vector3.hpp"
#include "shape.hpp"

class Shape;

class Intersection  {
public:
	Vector3 point;
	Vector3 normal;
	double distance;
	Shape* shape;
	Intersection() : point(Vector3(0,0,0)), normal(Vector3(0,0,1)), distance(INFINITY){};
};


#endif

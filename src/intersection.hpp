#ifndef __INTERSECTION__
#define __INTERSECTION__

#include <sstream>
#include "vector3.hpp"
#include "outputable.hpp"
#include "shape.hpp"

class Shape;

class Intersection : public Outputable {
public:
	Vector3 point;
	Vector3 normal;
	double distance;
	Shape* shape;
	Intersection() : point(Vector3(0,0,0)), normal(Vector3(0,0,1)), distance(INFINITY){};
	std::string str() const {
		std::stringstream ss;
		ss << "Intersection(";
		ss << "point=" << point;
		ss << "normal=" << normal;
		ss << ",distance=" << distance;
		ss << ")";
		return ss.str();
	}
};


#endif

#ifndef __SPHERE__
#define __SPHERE__
#include "shape.hpp"
#include <boost/lexical_cast.hpp>
#include "bbox.hpp"

class Sphere : public Shape{
public:
  Vector3 center;
  double radius;
  Sphere(Vector3 _center, double _radius) : center(_center),
					   radius(_radius){};
				Sphere(){};

	void setUp(std::multimap<std::string,std::string> m){
		std::multimap<std::string,std::string>::iterator result;
		result = m.find("center");
		if(result != m.end())
			center = Vector3::fromString(result->second);
		result = m.find("radius");
		if(result != m.end())
			radius = boost::lexical_cast<double>(result->second);
	}

  virtual bool intersect(const Ray &ray,
			 Intersection* intersection);
  virtual bool doesIntersect(const Ray &ray);

  virtual void computeBoundingBox();
  
};

#endif

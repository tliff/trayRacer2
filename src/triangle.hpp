#ifndef __TRIANGLE__
#define __TRIANGLE__
#include "shape.hpp"
#include "bbox.hpp"

#include <boost/serialization/serialization.hpp>



class Triangle : public Shape{
		friend class boost::serialization::access;
public:
  Vector3 p0, p1, p2;
  Vector3 normal;
Triangle(){};
  Triangle(Vector3 _p0, Vector3 _p1, Vector3 _p2) : p0(_p0),
						    p1(_p1),
						    p2(_p2){
    normal = (p0-p1).cross(p2-p1);
    normal.normalize();
  };

  virtual bool intersect(const Ray &ray,
			 Intersection* intersection);
  virtual bool doesIntersect(const Ray &ray);

  virtual void computeBoundingBox();

		template<class Archive>
		void serialize (Archive & ar,  const unsigned int version )
		{
			ar & p0;
			ar & p1;
			ar & p2;
			ar & normal;
		}



};
#endif

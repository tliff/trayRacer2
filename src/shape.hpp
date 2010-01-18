#ifndef __SHAPE__
#define __SHAPE__

#include "shader.hpp"
#include "ray.hpp"
#include "bbox.hpp"

#include "intersection.hpp"
#include <map>
#include <string>

class Shader;
class Intersection;
class Shape {
protected:
  BBox boundingBox;
  bool boundingBoxComputed;
  Shader* shader;
  
public:
  Shape(){
    boundingBoxComputed = false;
    shader = NULL;
  }
    
  virtual bool intersect(const Ray &ray,
			 Intersection* intersection)=0;
  virtual bool doesIntersect(const Ray &ray)=0;

  virtual void computeBoundingBox()=0;

  virtual BBox& getBBox(){
    if(!boundingBoxComputed){
      boundingBoxComputed=true;
      computeBoundingBox();
    }
    return boundingBox;
  }

 	virtual void setShader(Shader *shader){
 		this->shader = shader;
 	}

	virtual void setUp(std::multimap<std::string,std::string> m){}

	virtual Shader* getShader(){
		return this->shader;
	}

		friend class boost::serialization::access;
		template<class Archive>
		void serialize (Archive & ar,  const unsigned int version )
		{

		}
	

};

#endif

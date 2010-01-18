#include "triangle.hpp"

inline bool Triangle::doesIntersect(const Ray &ray){
  return intersect(ray, NULL);
}

inline bool Triangle::intersect(const Ray &ray,
				Intersection* intersection){
  Vector3 tvec, pvec, qvec;
  double det,inv_det;
  double t, u, v, w;
  
  // find vectors for two edges sharing vert0 
  const Vector3 edge1 = p1 - p0;
  const Vector3 edge2 = p2 - p0;
  
  // begin calculating determinant - also used to calculate U parameter
  pvec = ray.direction.cross(edge2);
  
  // if determinant is near zero, ray lies in plane of triangle
  det = edge1.dot(pvec);
  
 /* if (det > -EPSILON && det < EPSILON)
    return false;*/
  inv_det = 1.0 / det;
  
  // calculate distance from vert0 to ray origin
  tvec = ray.origin - p0;
  
  // calculate U parameter and test bounds
  
  u = tvec.dot(pvec) * inv_det;
  if (u < 0.0 || u > (1.0 + EPSILON))
    return false;
  
  // prepare to test V parameter
  qvec = tvec.cross(edge1);
  
  // calculate V parameter and test bounds
  v = ray.direction.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > (1.0+EPSILON))
    return false;
  
  w = (1.0 +EPSILON) - ( u + v);
  
  // calculate t, ray intersects triangle
  t = edge2.dot(qvec) * inv_det;
  if(t < 0) 
	  return false;
  //std::cout << "Tri intersected" << std::endl;
  if(t > intersection->distance)
	  return false;
  if(intersection == NULL)
    return true;
  

  if(normal.dot(ray.direction) > 0)
	normal = normal * -1;

  intersection->point = ray.origin + ray.direction*t;
  intersection->distance = t;
  intersection->normal = normal;

return true;
};


	

inline void Triangle::computeBoundingBox(){
  boundingBox = BBox(Vector3(std::min(std::min(p0.x, p1.x), p2.x),
			     std::min(std::min(p0.y, p1.y), p2.y),
			     std::min(std::min(p0.z, p1.z), p2.z)),
		     Vector3(std::max(std::max(p0.x, p1.x), p2.x),
			     std::max(std::max(p0.y, p1.y), p2.y),
			     std::max(std::max(p0.z, p1.z), p2.z)));
}


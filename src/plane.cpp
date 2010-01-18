#include "plane.hpp"
Plane::Plane ( Vector3 _base, Vector3 _normal ) : base ( _base ),
		normal ( _normal )
{
	shader = NULL;
	normal.normalize();
}

inline bool Plane::intersect ( const Ray &ray,
                                Intersection* intersection )
{
	double desc = normal.dot ( ray.direction *-1);


	//ray and plane are parallel
	if ( desc < EPSILON )
		return false;
	
	double dist = ( normal.dot ( ray.origin-base ) ) /desc;
	if(intersection && intersection->distance < dist)
		return false;
	
	if(intersection == NULL)
		return true;
	
	intersection->point = ray.origin + ray.direction*dist;
	intersection->normal = normal;	
	intersection->distance = dist;
	
	intersection->shape = this;
	
	return true;

}

inline bool Plane::doesIntersect ( const Ray &ray )
{
	return intersect(ray, NULL);
}

inline void Plane::computeBoundingBox()
{
	//we could remove one dimension for planes that are parallel
	//to an axis but we wont for now at least
	boundingBox = BBox ( Vector3 ( -INFINITY, -INFINITY, -INFINITY ),
	                     Vector3 ( INFINITY, INFINITY, INFINITY) );
}


Plane::~Plane()
{
}



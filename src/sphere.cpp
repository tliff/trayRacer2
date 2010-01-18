#include "sphere.hpp"

inline bool Sphere::doesIntersect ( const Ray &ray )
{
	return intersect ( ray, NULL );
}

inline bool Sphere::intersect ( const Ray &ray,
                                Intersection* intersection )
{
	Vector3 v = ray.origin - this->center;

	double desc = pow ( ray.direction.dot ( v ),2 ) - ray.direction.dot ( ray.direction ) * ( v.dot ( v ) - radius*radius );

	if ( desc < EPSILON )
		return false;
	desc = sqrt ( desc );
	Vector3 tmp = ray.direction* ( -1 );
	double dista = ( tmp.dot ( v ) + desc ) / ray.direction.dot ( ray.direction );
	double distb = ( tmp.dot ( v ) - desc ) / ray.direction.dot ( ray.direction );

	double swapvar;
	if ( dista > distb )
	{
		swapvar = dista;
		dista = distb;
		distb = swapvar;
	}
	if ( dista < EPSILON )
	{
		swapvar = dista;
		dista = distb;
		distb = swapvar;
	}
	if ( dista < EPSILON )
	{
		return false;
	}
	if ( intersection && intersection->distance > dista * ray.direction.getLength())
	{
		intersection->point = ray.origin + ray.direction*dista;
		intersection->normal = intersection->point - this->center;
		intersection->normal.normalize();
		intersection->distance = dista * ray.direction.getLength();
		intersection->shape = this;
	}
	return true;
};

inline void Sphere::computeBoundingBox()
{
	boundingBox = BBox ( center-Vector3 ( radius, radius, radius ),
	                     center+Vector3 ( radius, radius, radius ) );
}


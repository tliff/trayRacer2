#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"


class Plane : public Shape
{
	public:
		~Plane();

		Vector3 base;
		Vector3 normal;
		Plane ( Vector3 _base, Vector3 _normal );
		std::string str() const;

		virtual bool intersect ( const Ray &ray,
		                         Intersection* intersection );
		virtual bool doesIntersect ( const Ray &ray );

		virtual void computeBoundingBox();

};

#endif

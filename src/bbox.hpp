#ifndef __BBOX__
#define __BBOX__
#include "math/math.hpp"
#include "outputable.hpp"
#include <sstream>
#include <boost/serialization/serialization.hpp>


/**
 * \brief An axis-alligned bounding Box
 */

class BBox : public Outputable
{

	public:

		std::string str() const
		{
			std::stringstream ss;
			ss << "BBox("<<lowerBound << upperBound<<")";
			return ss.str();
		}
		/**
		 * \brief Determines wheter a ray intersects this box
		 * \returns true on hit, false on miss
		 */
	 	bool intersect ( const Ray &ray )
		{
			double foo;
			return intersect(ray, foo, foo);
		};

	 	bool intersect ( const Ray &ray, double &a, double &b )
		{
			double tmin, tmax, tymin, tymax, tzmin, tzmax;
			double divx, divy, divz;
			divx = 1 / ray.direction.x;
			if ( divx >= 0 )
			{
				tmin = ( lowerBound.x - ray.origin.x ) * divx;
				tmax = ( upperBound.x - ray.origin.x ) * divx;
			}
			else
			{
			//	std::cout << foo << std::endl;
			//s	std::cout << upperBound << ray << std::endl;
				tmin = ( upperBound.x - ray.origin.x ) * divx;
				tmax = ( lowerBound.x - ray.origin.x ) * divx;
			}
			divy = 1 / ray.direction.y;
			if ( divy >= 0 )
			{
				tymin = ( lowerBound.y - ray.origin.y ) * divy;
				tymax = ( upperBound.y - ray.origin.y ) * divy;
			}
			else
			{
				tymin = ( upperBound.y - ray.origin.y ) * divy;
				tymax = ( lowerBound.y - ray.origin.y ) * divy;
			}
			if ( ( tmin > ( tymax+EPSILON ) ) || ( tymin > ( tmax+EPSILON ) ) )
				return false;
			if ( tymin > tmin )
				tmin = tymin;
			if ( tymax < tmax )
				tmax = tymax;
			divz = 1 / ray.direction.z;
			if ( divz >= 0 )
			{
				tzmin = ( lowerBound.z - ray.origin.z ) * divz;
				tzmax = ( upperBound.z - ray.origin.z ) * divz;
			}
			else
			{
				tzmin = ( upperBound.z - ray.origin.z ) * divz;
				tzmax = ( lowerBound.z - ray.origin.z ) * divz;
			}
			if ( ( tmin > ( tzmax+EPSILON ) ) || ( tzmin > ( tmax+EPSILON ) ) )
				return false;
			if ( tzmin > tmin )
				tmin = tzmin;
			if ( tzmax < tmax )
				tmax = tzmax;
			a= tmin; b = tmax;
			return true;

		}

		BBox ( Vector3 l, Vector3 u ) : lowerBound ( l ),
				upperBound ( u ) {};
		BBox() : lowerBound ( Vector3 ( INFINITY,INFINITY,INFINITY ) ),
				upperBound ( Vector3 ( NEGINFINITY,NEGINFINITY,NEGINFINITY ) ) {};
		void addVector3 ( const Vector3 &v )
		{
			lowerBound.x = std::min ( lowerBound.x, v.x );
			lowerBound.y = std::min ( lowerBound.y, v.y );
			lowerBound.z = std::min ( lowerBound.z, v.z );
			upperBound.x = std::max ( upperBound.x, v.x );
			upperBound.y = std::max ( upperBound.y, v.y );
			upperBound.z = std::max ( upperBound.z, v.z );

		}

		Vector3 lowerBound, upperBound;

		friend class boost::serialization::access;
		template<class Archive>
		void serialize (Archive & ar,  const unsigned int version )
		{
			ar & lowerBound;
			ar & upperBound;
		}
};

#endif

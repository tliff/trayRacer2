#ifndef __PLANEETEST_HPP__
#define __PLANETEST_HPP__
#include "plane.hpp"
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_CASE (PlaneIntersectionTestDistance)
{
	Plane a(Vector3(3,5,10), Vector3(0,0,-1));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_CLOSE(i.distance, 10.0, 1e-3);
}
BOOST_AUTO_TEST_CASE (PlaneIntersectionTestPoint)
{
	Plane a(Vector3(3,5,10), Vector3(0,0,-1));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.point, Vector3(0,0,10));
}
BOOST_AUTO_TEST_CASE (PlaneIntersectionTestNormal)
{
	Plane a(Vector3(3,5,10), Vector3(0,0,-1));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.normal, Vector3(0,0,-1));
}


#endif


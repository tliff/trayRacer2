#ifndef __SPHERETEST_HPP__
#define __SPHERETEST_HPP__
#include "sphere.hpp"
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_CASE (SphereIntersectionTestDistance)
{
	Sphere a(Vector3(0,0,10), 3);
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_CLOSE(i.distance, 7.0, 1e-3);
}
BOOST_AUTO_TEST_CASE (SphereIntersectionTestPoint)
{
	Sphere a(Vector3(0,0,10), 3);
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.point, Vector3(0,0,7));
}
BOOST_AUTO_TEST_CASE (SphereIntersectionTestNormal)
{
	Sphere a(Vector3(0,0,10), 3);
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.normal, Vector3(0,0,-1));
}


#endif


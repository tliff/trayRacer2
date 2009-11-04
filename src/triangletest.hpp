#ifndef __TRIANGLETEST_HPP__
#define __TRIANGLETEST_HPP__
#include "triangle.hpp"
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_CASE (TriangleIntersectionTestDistance)
{
	Triangle a(Vector3(-10,-10,10), Vector3(20,10,10),Vector3(-10,10,10));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_CLOSE(i.distance, 10.0, 1e-3);
}
BOOST_AUTO_TEST_CASE (TriangleIntersectionTestPoint)
{
	Triangle a(Vector3(-10,-10,10), Vector3(20,10,10),Vector3(-10,10,10));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.point, Vector3(0,0,10));
}
BOOST_AUTO_TEST_CASE (TriangleIntersectionTestNormal)
{
	Triangle a(Vector3(-10,-10,10), Vector3(20,10,10),Vector3(-10,10,10));
	Ray r(Vector3(0,0,0),Vector3(0,0,1));
	Intersection i;
	a.intersect(r, &i);
	BOOST_CHECK_EQUAL(i.normal, Vector3(0,0,-1));
}


#endif


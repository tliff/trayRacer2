#ifndef __BBOXTEST_HPP__
#define __BBOXTEST_HPP__
#include "bbox.hpp"
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_CASE (BBoxTest)
{
	BBox b(Vector3(INFINITY,INFINITY,INFINITY), Vector3(NEGINFINITY,NEGINFINITY,NEGINFINITY));
	double min, max;
	b.addVector3(Vector3(-10,-10,5));
	b.addVector3(Vector3(10,10,10));
	Ray r(Vector3(0,0,0), Vector3(0,0,1));
	b.intersect(r, min, max);
	BOOST_CHECK_CLOSE(min, 5.0, 1e-3);
	BOOST_CHECK_CLOSE(max, 10.0, 1e-3);
}

#endif

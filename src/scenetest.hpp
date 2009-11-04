#ifndef __SCENETEST_HPP__
#define __SCENETEST_HPP__
#include "scene.hpp"
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_CASE (SceneTestCanSeeDirection)
{
	Scene s;
	s.addShape(new Plane(Vector3(0,0,5),Vector3(0,0,-1)));
	BOOST_CHECK(!s.canSee(Vector3(0,0,0), Vector3(10,10,10)));
}

BOOST_AUTO_TEST_CASE (SceneTestCanSeeDirectionInverse)
{
	Scene s;
	s.addShape(new Plane(Vector3(0,0,5),Vector3(0,0,-1)));
	BOOST_CHECK(s.canSee(Vector3(10,10,10), Vector3(0,0,0)));
}

BOOST_AUTO_TEST_CASE (SceneTestCanSeeClose)
{
	Scene s;
	s.addShape(new Plane(Vector3(0,0,5),Vector3(0,0,-1)));
	BOOST_CHECK(s.canSee(Vector3(0,0,4.999), Vector3(0,0,0)));
}
#endif

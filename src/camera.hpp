#ifndef __CAMERA__
#define __CAMERA__
#include <string>
#include <map>
#include "ray.hpp"
#include "math/math.hpp"
#include "math/matrix44.hpp"
#include "plugin.hpp"

/**
 * A camera takes care to map coordinates from
 * a render buffer to a ray we need to cast.
 */
class Camera : public Plugin {
public:

  /**
   * Finds out what ray to cast for a buffer-coordinate
   * \param x The x value for the ray to generate
   * \param y The y value for the ray to generate
   * \returns A ray
   */
  virtual Ray constructViewRay(double x, double y)=0;

  Camera(Vector3 pos, Vector3 lookAt, Vector3 up, double povw, double povh){
	setUp(pos, lookAt, up, povw, povh);
  }

  Camera(double povw, double povh){
	setUp(Vector3(0,0,0), Vector3(0,0,1), Vector3(0,1,0), povw, povh);
  }

  Camera(){
	setUp(Vector3(0,0,0), Vector3(0,0,1), Vector3(0,1,0), 0.5*M_PI, 0.5*M_PI);
  }

	void setUp(Vector3 pos, Vector3 lookAt, Vector3 up, double povw, double povh){
		transform = Matrix44::lookAt(pos, lookAt, up);
		origin = transform * Vector3(0,0,0);
		double hHalf = tan(povh*0.5);
		double wHalf = tan(povw*0.5);
// 		std::cout << "========================================" << std::endl;
// 
// 		std::cout << transform << std::endl;
 //		std::cout << "From: " << pos << std::endl;
// 
 //		std::cout << "Look: " << lookAt << std::endl;
// 
 //		std::cout << "Up:   " << up << std::endl;
// 
// 		std::cout << "Origin: " << origin << std::endl;
// 
//  		std::cout << "hHalf: " << hHalf << "  wHalf: " << wHalf << std::endl;

		p = transform * Vector3(-wHalf, -hHalf, 1);
		Vector3 px = transform * Vector3(wHalf, -hHalf, 1);
		Vector3 py = transform * Vector3(-wHalf, hHalf, 1);

// 		std::cout << "p: "<<p <<" px: "<<px << " py: " << py << std::endl;

		vx = px - p;
		vy = py - p;
		
// 		std::cout << "p: "<<p <<" vx: "<<vx << " vy: " << vy << std::endl;
// 		std::cout << "========================================" << std::endl;
	}
	void setUp(std::multimap<std::string,std::string> m){
		Vector3 position(0,0,10);
		Vector3 lookAt;
		Vector3 up;
		double povw = 0.5 * M_PI;
		double povh = 0.5 * M_PI;
		
		std::multimap<std::string,std::string>::iterator result;
		
		result = m.find("position");
		if(result != m.end())
			position = Vector3::fromString(result->second);
		
		
		result = m.find("lookat");
		if(result != m.end())
			lookAt = Vector3::fromString(result->second);
			
		result = m.find("up");
		if(result != m.end())
			up = Vector3::fromString(result->second);
			
		result = m.find("povw");
		if(result != m.end())
			povw = boost::lexical_cast<double>(result->second);

		result = m.find("povh");
		if(result != m.end())
			povh = boost::lexical_cast<double>(result->second);

		setUp(position, lookAt, up, povw, povh);
	}

protected:
	Matrix44 transform;
	Vector3 origin;
	Vector3 p, vx, vy;


};

#endif

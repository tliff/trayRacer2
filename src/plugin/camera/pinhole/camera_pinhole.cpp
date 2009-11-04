#include "camera_pinhole.hpp"

Ray CameraPinhole::constructViewRay(double x, double y){
	Vector3 d =(p+vx*x+vy*y)-origin;
	d.normalize();
	return Ray(origin, d);
}

TRAYRACER_PLUGIN_EXPORT("camera", "pinhole", CameraPinhole);

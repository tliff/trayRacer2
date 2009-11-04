#ifndef __CAMERA_PINHOLE__
#define __CAMERA_PINHOLE__

#include <string>
#include <camera.hpp>

class CameraPinhole : public Camera {
  virtual Ray constructViewRay(double x, double y);
};


#endif

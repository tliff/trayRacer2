#ifndef __SCENELOADER__
#define __SCENELOADER__

#include "plugin.hpp"
#include <string>
#include "scene.hpp"

class SceneLoader {
 public:
  virtual bool loadSceneFromFile(Scene* scene, std::string filename){return false;};
  SceneLoader(){};
  virtual ~SceneLoader(){};
};

#endif

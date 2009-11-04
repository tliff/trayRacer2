#ifndef __SCENELOADER_TEST__
#define __SCENELOADER_TEST__

#include <string>
#include "../../../sceneloader.hpp"

class SceneLoaderTest : public SceneLoader {
  virtual bool loadSceneFromFile(Scene* scene, std::string filename);

};


#endif

#ifndef __SCENELOADER_XML__
#define __SCENELOADER_XML__

#include <string>
#include <sceneloader.hpp>

class SceneLoaderXml : public SceneLoader {
  virtual bool loadSceneFromFile(Scene* scene, std::string filename);

};


#endif

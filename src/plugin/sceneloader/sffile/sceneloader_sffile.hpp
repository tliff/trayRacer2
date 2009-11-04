#ifndef __SCENELOADER_SFFILE__
#define __SCENELOADER_SFFILE__

#include <string>
#include <sceneloader.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/any.hpp>
#include <map>

class SceneLoaderSFFile : public SceneLoader {
bool loadSceneFromFile(Scene* scene, std::string filename);


};


#endif

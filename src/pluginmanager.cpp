#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/regex.hpp"
#include <iostream>

#include "pluginmanager.hpp"

#ifdef _WIN32
#include <windows.h>
#define DLSYM GetProcAddress
#else
#include <dlfcn.h>
#define DLSYM dlsym
#endif

namespace trayRacer{

	PluginManager PluginManager::instance;

	void PluginManager::registerPlugin(std::string type, 
				   	std::string identifier, 
				   	void* fun){
		plugins[type][identifier] = fun;
	}


	Plugin* PluginManager::getPlugin(std::string type,
			   std::string identifier){
  		Plugin* (*myPlugin)() = (Plugin* (*)())plugins[type][identifier];
		if(!myPlugin){
		  std::cout << std::endl << "PLUGIN MANAGER: Unable to create an " <<
		    "instance of "<< type << ":" << identifier << std::endl;
		  return NULL;
		}
		return myPlugin();
	}

	PluginManager& PluginManager::getInstance(){
  		return instance;
	}

	void PluginManager::loadPlugins(std::string path){
	  if(path == "")
	    path = "plugin";
	  
	  //set up the regex to match
#ifdef _WIN32	  
	  static const boost::regex libRegex("tr.*\\.dll");
#else
	  static const boost::regex libRegex("libtr.*\\.so");
#endif
  
	  //first try ./plugins/
	  if(!boost::filesystem::is_directory(path))
	    return;
	  boost::filesystem::directory_iterator end_itr;
	  for( boost::filesystem::directory_iterator itr(path);
	       itr != end_itr;
	       ++itr ) {
	    if(boost::filesystem::is_directory(itr->string()))
	      loadPlugins(itr->string());
	    if(regex_match(itr->leaf(), libRegex)){
	      loadPlugin(itr->string());
	    }
	  }
	}

	bool PluginManager::loadPlugin(std::string file){
	  //load the so
	  std::cout << "Loading " << file << " ... ";
	  std::string error = "";
#ifdef _WIN32
	  HMODULE libHandle = LoadLibrary(file.c_str());
	  if(libHandle == NULL){
	    std::cout << "Got an error!" << std::endl; 
	    return false;
	  }
#else
	  void* libHandle = dlopen(file.c_str(), RTLD_NOW | RTLD_GLOBAL);
	  if(libHandle == NULL){
	    std::cout << "Got an error: " << dlerror() << std::endl; 
	    return false;
	  }
#endif
	  std::cout << "done" << std::endl;
	  //find the init function
	  void* initFunction = (void*)DLSYM(libHandle, "plugin_init"); 

	  if(initFunction == NULL){
	    std::cout << "Got an error!" << std::endl; 
	    return false;
	  }
  
	  std::string type, id;

	  std::string (*fun)() = (std::string (*)())DLSYM(libHandle, "plugin_type");
	  type = fun();

	  fun = (std::string (*)())DLSYM(libHandle, "plugin_id");
	  id = fun();


	  registerPlugin(type, id, initFunction);
	  return true;
	}
};

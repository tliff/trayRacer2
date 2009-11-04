#ifndef __PLUGIN_MANAGER__
#define __PLUGIN_MANAGER__

#include <string>
#include <map>
#include <boost/function.hpp>

#include "plugin.hpp"

#define CREATE_PLUGIN_INSTANCE(x,y) \
	::trayRacer::PluginManager::getInstance().getPlugin(x, y)

namespace trayRacer{
	class PluginManager {
 	protected:
    	std::map< std::string, std::map<std::string, void* > > plugins;
    	static PluginManager instance;

    	bool loadPlugin(std::string);

 	public:
    	void registerPlugin(std::string type,
				std::string identifier, 
				void* function);
    
    	Plugin* getPlugin(std::string type, std::string identifier);

    	static PluginManager& getInstance();
    
    	void loadPlugins(std::string path = "");

	};
};
#endif

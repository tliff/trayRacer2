#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include <string>

#define TRAYRACER_PLUGIN_EXPORT(t, id, x) \
extern "C" { \
    Plugin* plugin_init() \
    { \
        return new x;\
    } \
    std::string plugin_type(){ \
        return t; \
    } \
    std::string plugin_id(){ \
        return id;\
    } \
} 

class Plugin {
 public:
  Plugin();
  virtual ~Plugin();
};

#endif

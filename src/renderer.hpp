#ifndef __RENDERER__
#define __RENDERER__
#include "plugin.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "renderobserver.hpp"
#include "rendersurface.hpp"
#include <vector>

class Renderer {
protected:
	std::vector<RenderObserver*> observers;
	
	inline void reportProgress(int x, int y, int w, int h){
		for(std::vector<RenderObserver*>::iterator it = observers.begin();
			it != observers.end();
			++it){
				(*it)->reportProgress(raysDone, raysEstimated, x, y, w, h);
		}
	}
	
	inline void reportStart(){
			for(std::vector<RenderObserver*>::iterator it = observers.begin();
			it != observers.end();
			++it){
				(*it)->reportStart();
		}	
	}
	
	inline void reportEnd(){
			for(std::vector<RenderObserver*>::iterator it = observers.begin();
			it != observers.end();
			++it){
				(*it)->reportEnd();
		}	
	}
	
	inline void setObserverSurface(RenderSurface* r){
		for(std::vector<RenderObserver*>::iterator it = observers.begin();
			it != observers.end();
			++it){
				(*it)->setSurface(r);
		}	
	}
	
	long raysDone;
	long raysEstimated;
	
public:
  Renderer() : raysDone(0), raysEstimated(0){};
  ~Renderer(){};
  virtual void render(Scene*, Camera*, RenderSurface*)=0;
  virtual void addObserver(RenderObserver* r){
	  observers.push_back(r);
  }
};

#endif


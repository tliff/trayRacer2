#ifndef RENDEROBVERSER_HPP
#define RENDEROBVERSER_HPP
#include <boost/timer.hpp>

#include "plugin.hpp"
#include "rendersurface.hpp"

class RenderObserver {
protected:
	boost::timer timer;
	RenderSurface* surface;
public:
    RenderObserver(){
		surface = NULL;
	};
	
	virtual void setSurface(RenderSurface* surface){
		this->surface = surface;
	}

	virtual void reportStart(){
		timer.restart();
		customStart();
	}
	
	virtual void customStart(){
	}
	
	virtual void reportEnd(){};
	
	virtual void reportProgress(long raysDone, long raysEstimated,
						int x, int y, int w, int h)=0;
	
    ~RenderObserver(){};

};

#endif

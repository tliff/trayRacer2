#ifndef __RENDEROBSERVER_CONSOLE__
#define __RENDEROBSERVER_CONSOLE__

#include <string>
#include <renderobserver.hpp>

class RenderObserverConsole : public RenderObserver {
public:
    RenderObserverConsole();

	void reportEnd();
	
	void reportProgress(long raysDone, long raysEstimated,
						int x, int y, int w, int h);
    ~RenderObserverConsole();

};


#endif

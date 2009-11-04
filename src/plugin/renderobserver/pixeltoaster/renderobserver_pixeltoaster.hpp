#ifndef __RENDEROBSERVER_PIXELTOASTER__
#define __RENDEROBSERVER_PIXELTOASTER__

#include <string>
#include <vector>
#include <renderobserver.hpp>
#include <pixeltoaster/PixelToaster.h>

class RenderObserverPixeltoaster : public RenderObserver {
	protected:
		PixelToaster::Display* display;
		int w, h;
		std::vector<PixelToaster::FloatingPointPixel> pixels;
	public:
    RenderObserverPixeltoaster();

	void customStart();
	void reportEnd();
	
	void reportProgress(long raysDone, long raysEstimated,
						int x, int y, int w, int h);
    ~RenderObserverPixeltoaster();

};


#endif

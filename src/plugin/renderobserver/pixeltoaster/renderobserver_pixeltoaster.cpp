#include "renderobserver_pixeltoaster.hpp"
#include <iostream>

RenderObserverPixeltoaster::RenderObserverPixeltoaster()
{

}

void RenderObserverPixeltoaster::reportEnd()
{
}

void RenderObserverPixeltoaster::customStart()
{
	w = surface->getWidth();
	h = surface->getHeight();
	display = new PixelToaster::Display( "trayRacer2", w, h );
	pixels.resize(w*h);
}

void RenderObserverPixeltoaster::reportProgress ( long raysDone, long raysEstimated,
        int x, int y, int w, int h )
{
	Color c;
	for(int _y = y; _y < y +h; _y++){
		for(int _x = x; _x < x +w; _x++){
			c = surface->getPixel(_x,_y);
			if(!(_x >= this->w) && !(_y >= this->h))
			pixels[this->w*_y+_x]= PixelToaster::FloatingPointPixel(c.r/(1+c.r), c.g/(1+c.g), c.b/(c.b+1));
		}
	}
	display->update(pixels);
}
RenderObserverPixeltoaster::~RenderObserverPixeltoaster()
{

}

TRAYRACER_PLUGIN_EXPORT ( "renderobserver", "pixeltoaster", RenderObserverPixeltoaster );

#include "scalingtonemapper.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>

bool ScalingToneMapper::map(RenderSurface* renderSurface, RGBSurface* outputSurface){
	if(renderSurface->getWidth()  != outputSurface->getWidth() || renderSurface->getHeight() != outputSurface->getHeight())
		return false;
	int w = renderSurface->getWidth();
	int h = renderSurface->getHeight();
	float maxr=0, maxg=0, maxb=0;
	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			Color c = renderSurface->getPixel(x,y).gamma(gamma);
			maxr = std::max(maxr, c.r);
			maxg = std::max(maxr, c.g);
			maxb = std::max(maxr, c.b);
		}
	}
	float scaleFactor = std::max(std::max(maxr, maxg), maxb);
// 	std::cout << maxr << maxg << maxb << std::endl;
	scaleFactor = scaleFactor != 0 ? scaleFactor : 1;
	scaleFactor = 255.0f/scaleFactor;
// 	std::cout << "Scale factor is " << scaleFactor << std::endl;
	
	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			Color c;
			c = renderSurface->getPixel(x,y).gamma(gamma);
			c = c*scaleFactor;

			outputSurface->setPixel(x,y, c);
		}
	}	
		
	return true;
}

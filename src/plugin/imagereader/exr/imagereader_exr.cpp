#include "imagereader_exr.hpp"
#include <color.hpp>
#include <ImfOutputFile.h>
#include <ImfChannelList.h>
#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <ImfStdIO.h>
#include <ImfVersion.h>

bool ImageReaderExr::read(std::ifstream &stream, RGBSurface* surface){
	using namespace Imf;
	using namespace Imath;
	StdIFStream istream(stream, "");
	RgbaInputFile file (istream); 
	Box2i dw = file.dataWindow(); 
	int width  = dw.max.x - dw.min.x + 1; 
	int height = dw.max.y - dw.min.y + 1; 
	Array<Rgba> pixels;
	pixels.resizeErase (height* width);
	surface->resize(width, height);
	file.setFrameBuffer (&pixels[0] - dw.min.x - dw.min.y * width, 1, width); 
	file.readPixels (dw.min.y, dw.max.y);
	
	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			float r, g, b;
			r = pixels[x+y*width].r;
			g = pixels[x+y*width].g;
			b = pixels[x+y*width].b;
			surface->setPixel(x,y,Color(r,g,b));
		}		
	}
	
	return true;
}
TRAYRACER_PLUGIN_EXPORT("imagereader", "exr", ImageReaderExr);

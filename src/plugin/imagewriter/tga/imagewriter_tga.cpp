#include "imagewriter_tga.hpp"

bool ImageWriterTGA::write(std::ostream &stream, RGBSurface* surface){
// 	std::cout << "called" << std::endl;
	int width = surface->getWidth();
	int height = surface->getHeight();
// 	std::cout << "Writing a " << width << "x" << height<< " image"<< std::endl;
	//write the tga-header
	stream.put((char)0x00); //no id
	stream.put((char)0x00); //no palette
	stream.put((char)0x02); //uncompressed truecolor
	stream.put((char)0x00); //no palette
	stream.put((char)0x00); //no palette
	stream.put((char)0x00); //no palette
	stream.put((char)0x00); //no palette
	stream.put((char)0x00); //no palette
	stream.put((char)0x00); //origin x
	stream.put((char)0x00); //origin x
	stream.put((char)0x00); //origin y
	stream.put((char)0x00); //origin y
	stream.put((char) (width%256)); // width
	stream.put((char) (width/256)); // width
	stream.put((char) (height%256)); // height
	stream.put((char) (height/256)); // height
	stream.put((char)0x20); //32bit color
	stream.put((char)0x00); //8bit alpha-channel
	
	
	for(int y=height-1; y >= 0; y--){
		for(int x = 0; x < width; x++)
		{
			Color pixel = surface->getPixel(x,y);
			stream.put((int)pixel.b);
			stream.put((int)pixel.g);
			stream.put((int)pixel.r);
			stream.put(255);
		}
	}
	return true;
}

TRAYRACER_PLUGIN_EXPORT("imagewriter", "tga", ImageWriterTGA);

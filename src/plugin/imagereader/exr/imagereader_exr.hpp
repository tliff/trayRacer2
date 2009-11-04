#ifndef __IMAGEREADER_EXR__
#define __IMAGEREADER_EXR__

#include <string>
#include <imagereader.hpp>

class ImageReaderExr : public ImageReader {
	  virtual bool read(std::ifstream &stream, RGBSurface* surface);
};


#endif

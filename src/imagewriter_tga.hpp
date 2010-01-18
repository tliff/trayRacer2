#ifndef __IMAGEWRITER_TGA__
#define __IMAGEWRITER_TGA__

#include <string>
#include <iostream>
#include <fstream>
#include <imagewriter.hpp>


class ImageWriterTGA : public ImageWriter {
public:
  bool write(std::ostream &stream, RGBSurface* surface);
  std::string encode(RGBSurface* surface);
};


#endif

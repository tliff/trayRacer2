#ifndef __IMAGEREADER_HPP__
#define __IMAGEREADER_HPP__
#include "plugin.hpp"
#include "rgbsurface.hpp"
#include <string>

class ImageReader : public Plugin {
public:
  ImageReader(){}
  ~ImageReader(){}
  virtual bool read(std::ifstream &stream, RGBSurface* surface)=0;
};

#endif

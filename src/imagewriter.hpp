#ifndef __IMAGEWRITER_HPP__
#define __IMAGEWRITER_HPP__
#include "plugin.hpp"
#include "rgbsurface.hpp"
#include <string>

class ImageWriter : public Plugin {
public:
  ImageWriter(){}
  ~ImageWriter(){}
  virtual bool write(std::ostream &stream, RGBSurface* surface)=0;
};

#endif

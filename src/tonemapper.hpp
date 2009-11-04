#ifndef __TONEMAPPER_HPP__
#define __TONEMAPPER_HPP__
#include "rendersurface.hpp"
#include "rgbsurface.hpp"

class ToneMapper{
public:
  virtual bool map(RenderSurface* renderSurface, RGBSurface* outputSurface)=0;
};

#endif

#ifndef __SCALINGTONEMAPPER_HPP__
#define __SCALINGTONEMAPPER_HPP__
#include "rgbsurface.hpp"
#include "tonemapper.hpp"

class ScalingToneMapper : public ToneMapper {
	float gamma;
public:
	ScalingToneMapper() : gamma(1.8){};
	virtual bool map(RenderSurface* renderSurface, RGBSurface* outputSurface);
};

#endif

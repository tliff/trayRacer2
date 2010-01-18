%module "Trayracer::Base"
%include "std_string.i"

%{
	/* Includes the header in the wrapper code */
#include "vector3.hpp"
#include "color.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "pluginmanager.hpp"
#include "shape.hpp"
#include "meshkd.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "camera.hpp"
#include "camera_pinhole.hpp"
#include "renderer.hpp"
#include "renderer_default.hpp"
#include "pixelbuffer.hpp"
#include "rendersurface.hpp"
#include "rgbsurface.hpp"
#include "renderobserver_console.hpp"
#include "imagewriter.hpp"
#include "imagewriter_tga.hpp"
#include "scalingtonemapper.hpp"
%}



/* Parse the header file to generate wrappers */
%include "vector3.hpp"
%include "color.hpp"
%include "scene.hpp"
%include "light.hpp"
%include "pluginmanager.hpp"
%include "shape.hpp"
%include "meshkd.hpp"
%include "sphere.hpp"
%include "triangle.hpp"
%include "plane.hpp"
%include "camera.hpp"
%include "camera_pinhole.hpp"
%include "renderer.hpp"
%include "renderer_default.hpp"
%include "pixelbuffer.hpp"
%include "rendersurface.hpp"
%include "rgbsurface.hpp"
%include "renderobserver_console.hpp"
%include "imagewriter.hpp"
%include "imagewriter_tga.hpp"
%include "scalingtonemapper.hpp"


%template(RGBSurface) PixelBuffer<Color>;

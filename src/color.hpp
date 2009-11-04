#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "outputable.hpp"
#include <math.h>
#include <sstream>


class Color : public Outputable {
public:
	float r, g, b, a;

	//operators
	Color(): r(0), g(0), b(0), a(1){};
	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{
		
	}
	
	inline Color operator+(const Color& c) const {
		return Color(r+c.r,g+c.g,b+c.b);
	}

	inline Color operator*(double f) const {
		return Color(r*f, g*f, b*f);
	}

	inline Color operator*(const Color& c) const {
		return Color(r*(c.r),g*(c.g),b*(c.b));
	}
	
	std::string str() const {
		std::stringstream ss;
		ss << "Color(" << r << "," <<g<< ","<<b << ");";
		return ss.str();
	}
	
	inline Color gamma(const double gamma) const{
		double ginv = 1/gamma;
		return Color(pow(r,ginv), pow(g,ginv), pow(b,ginv));
	}
	
};

#endif

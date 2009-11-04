#ifndef __MATH_MATH_HPP
#define __MATH_MATH_HPP
#include <math.h>
#include <limits>
//#include "matrix44.hpp"
#include "functions.hpp"

//redefine Pi
#ifdef M_PI
#undef M_PI
#endif
#define M_PI 3.14159265358979323846f
#define INV_PI  0.31830988618379067154f
#define INV_TWOPI  0.15915494309189533577f
#define EPSILON 1.0E-5

//infinity is the maximum possible value for floats
#ifndef INFINITY
#define INFINITY std::numeric_limits<double>::max()
#endif

#ifndef NEGINFINITY
#define NEGINFINITY std::numeric_limits<double>::min()
#endif


#endif


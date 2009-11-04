
#ifndef TRANSFORMEDSHAPE_H
#define TRANSFORMEDSHAPE_H

#include "shape.hpp"
#include "math/matrix44.hpp"

class TransformedShape : public Shape
{
public:
    TransformedShape();
	TransformedShape(Shape* s);
	TransformedShape(Shape* s, Matrix44 m);

    ~TransformedShape();

};

#endif

#pragma once

#include "point.h"


struct IntRectangle {
	IntPoint topLeft;
	IntPoint bottomRight;
};

int getWidth(const IntRectangle& rect);

int getHeight(const IntRectangle& rect);

IntPoint getCenter(const IntRectangle& rect);

RealPoint getRealCenter(const IntRectangle& rect);

IntPoint getTopRight(const IntRectangle& rect);

IntPoint getBottomLeft(const IntRectangle& rect);

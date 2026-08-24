#pragma once

#include "point.h"


struct IntRectangle {
	IntPoint topLeft;
	IntPoint bottomRight;
};

bool isValid(const IntRectangle& rect);

int getWidth(const IntRectangle& rect);

int getHeight(const IntRectangle& rect);

IntPoint getCenter(const IntRectangle& rect);

RealPoint getRealCenter(const IntRectangle& rect);

IntPoint getTopRight(const IntRectangle& rect);

IntPoint getBottomLeft(const IntRectangle& rect);

std::string toString(const IntRectangle& rect,
	const std::string& rectPrefix = "[",
	const std::string& rectSeparator = " x ",
	const std::string& rectSuffix = "]",
	const std::string& pointPrefix = "(",
	const std::string& pointSeparator = ", ",
	const std::string& pointSuffix = ")");
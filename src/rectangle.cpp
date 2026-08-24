#include "../include/rectangle.h"

#include "iomanip"
#include <sstream>

bool isValid(const IntRectangle& rect) {
	return (rect.bottomRight.x >= rect.topLeft.x && rect.bottomRight.y >= rect.topLeft.y);
}

int getWidth(const IntRectangle& rect) {
	return (rect.bottomRight.x - rect.topLeft.x + 1);
}

int getHeight(const IntRectangle& rect) {
	return (rect.bottomRight.y - rect.topLeft.y + 1);
}

IntPoint getTopRight(const IntRectangle& rect) {
	return { rect.bottomRight.x, rect.topLeft.y };
}

IntPoint getBottomLeft(const IntRectangle& rect) {
	return { rect.topLeft.x, rect.bottomRight.y };
}

IntPoint getCenter(const IntRectangle& rect) {
	return { (int)std::round((rect.topLeft.x + rect.bottomRight.x) / 2),
			 (int)std::round((rect.topLeft.y + rect.bottomRight.y) / 2) };
}

RealPoint getRealCenter(const IntRectangle& rect) {
	return { (double(rect.topLeft.x) + rect.bottomRight.x) / 2, 
			 (double(rect.topLeft.y) + rect.bottomRight.y) / 2 };
}

std::string toString(const IntRectangle& rect,
					 const std::string& rectPrefix,
					 const std::string& rectSeparator,
					 const std::string& rectSuffix,
					 const std::string& pointPrefix,
					 const std::string& pointSeparator,
					 const std::string& pointSuffix) {
	std::stringstream ss;

	ss << rectPrefix << pointPrefix 
		<< rect.topLeft.x << pointSeparator << rect.topLeft.y << pointSuffix
		<< rectSeparator << pointPrefix << rect.bottomRight.x << pointSeparator 
		<< rect.bottomRight.y << pointSuffix << rectSuffix;

	return ss.str();
}
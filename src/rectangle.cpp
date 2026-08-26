#include "rectangle.h"

#include <cmath>

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

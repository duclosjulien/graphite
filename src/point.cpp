#include <cmath>
#include <sstream>
#include <iomanip>

#include "point.h"

RealPoint toReal(const IntPoint& point) {
	return { double(point.x), double(point.y) };
}

IntPoint toInt(const RealPoint& point) {
	return { (int)std::round(point.x), (int)std::round(point.y) };
}

std::string toString(const IntPoint& point, const std::string& prefix, const std::string& separator, const std::string& suffix) {
	return prefix + std::to_string(point.x) + separator + std::to_string(point.y) + suffix;
}

std::string toString(const RealPoint& point, size_t precision, const std::string& prefix, const std::string& separator , const std::string& suffix) {

	std::stringstream ss;
	ss << prefix
		<< std::fixed << std::setprecision(precision) << point.x
		<< separator
		<< std::fixed << std::setprecision(precision) << point.y
		<< suffix;
		return ss.str();
}
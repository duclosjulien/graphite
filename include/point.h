#pragma once

#include <string>


struct IntPoint  {
	int x, y;
};

struct RealPoint  {
	double x, y;
};

RealPoint toReal(const IntPoint& point);
IntPoint toInt(const RealPoint& point);

std::string toString(const IntPoint& point,
	const std::string& prefix = "(",
	const std::string& separator = ", ",
	const std::string& suffix = ")");

std::string toString(const RealPoint& point,
	size_t precision = 2,
	const std::string& prefix = "(",
	const std::string& separator = ", ",
	const std::string& suffix = ")");
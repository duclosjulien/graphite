#pragma once

#include <string>


struct IntPoint  {
	int x, y;
};

struct RealPoint  {
	double x, y;
};

RealPoint toReal(const IntPoint& point);

std::string toString(const IntPoint& point,
	const std::string& prefix = "(",
	const std::string& separator = ", ",
	const std::string& suffix = ")");

std::string toString(const RealPoint& point,
	int precision = 2,
	const std::string& prefix = "(",
	const std::string& separator = ", ",
	const std::string& suffix = ")");

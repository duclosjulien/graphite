#pragma once

#include <cstddef>
#include <string>

#include "colors.h"
#include "rectangle.h"


enum class BoxOutlineStyle {
	SimpleAscii,
	SingleLine,
	DoubleLine,
	MixedSimpleHDoubleV,
	MixedDoubleHSingleV,
	Uniform,
};

struct Box {
	IntRectangle geometry;

	char fillChar;
	Colors fillColors;

	BoxOutlineStyle outlineStyle;
	Colors outlineColors;
	char optionalOutlineUniformChar;

	std::string title;
	Colors textColors;

	std::string status;
	Colors statusColors;
};

void initialize(Box& box,
	const IntRectangle& geometry,
	const std::string& title = "",
	const std::string& status = "");

void draw(const Box& box);

void draw(const Box box[], std::size_t size);

void draw();

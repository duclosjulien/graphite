#pragma once

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

bool isValid(const Box& box);

IntPoint boxToScreenCoord(const IntPoint& coord, const Box& box);
IntPoint screenToBoxCoord(const IntPoint& coord, const Box& box);

void drawSurface(const Box& box);

void drawOutline(const Box& box);

void drawTitle(const Box& box, int width);

void draw(const Box& box);

void draw(Box box[]);

void draw();


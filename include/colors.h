#pragma once

enum class Color {
	blk,
	red,
	grn,
	ylw,
	blu,
	mag,
	cyn,
	wht,

	gry,
	_red,
	_grn,
	_ylw,
	_blu,
	_mag,
	_cyn,
	_wht
};

struct Colors  {
	Color background;
	Color foreground;
};

void setColors(const Colors& colors);

#include "../include/terminal.h"

void setColors(const Colors& colors) {
	setcolor(colors.background, colors.foreground);
}

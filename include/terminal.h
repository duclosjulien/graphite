#pragma once

#include "colors.h"

void setcolor(Color background, Color foreground);
void gotoxy(int x, int y);
void show(bool visible);
void restoreTerminal();

int getch();
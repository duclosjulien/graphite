#pragma once

#include <optional>

#include "colors.h"

struct TerminalSize {
    int width;
    int height;
};

std::optional<TerminalSize> getTerminalSize();

void setcolor(Color background, Color foreground);
void gotoxy(int x, int y);
void show(bool visible);
void restoreTerminal();
int getch();
void clearScreen();
void enterAlternateScreen();
void leaveAlternateScreen();

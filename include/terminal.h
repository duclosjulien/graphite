#pragma once

#include <optional>

#include "colors.h"

struct TerminalSize {
    int width;
    int height;
};

namespace Key {
    inline constexpr int Escape = 27;
    inline constexpr int ArrowUp = 256;
    inline constexpr int ArrowDown = 257;
    inline constexpr int ArrowLeft = 258;
    inline constexpr int ArrowRight = 259;
}

std::optional<TerminalSize> getTerminalSize();

void setcolor(Color background, Color foreground);
void gotoxy(int x, int y);
void show(bool visible);
void restoreTerminal();
int getch();
void clearScreen();
void enterAlternateScreen();
void leaveAlternateScreen();
int getKey();


#include "terminal.h"

#include <cstdio>
#include <iostream>
#include <termios.h>
#include <unistd.h>

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void show(bool visible) {
    std::cout << (visible ? "\033[?25h" : "\033[?25l");
}

void setcp(int) {
    // No-op on macOS/Linux.
}

int getch() {
    termios oldSettings{};
    termios newSettings{};

    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return ch;
}

void setcolor(Color background, Color foreground) {
    int bg;
    int fg;

    switch (background) {
        case Color::blk:  bg = 40;  break;
        case Color::red:  bg = 41;  break;
        case Color::grn:  bg = 42;  break;
        case Color::ylw:  bg = 43;  break;
        case Color::blu:  bg = 44;  break;
        case Color::mag:  bg = 45;  break;
        case Color::cyn:  bg = 46;  break;
        case Color::wht:  bg = 47;  break;

        case Color::gry:  bg = 100; break;
        case Color::_red: bg = 101; break;
        case Color::_grn: bg = 102; break;
        case Color::_ylw: bg = 103; break;
        case Color::_blu: bg = 104; break;
        case Color::_mag: bg = 105; break;
        case Color::_cyn: bg = 106; break;
        case Color::_wht: bg = 107; break;
    }

    switch (foreground) {
        case Color::blk:  fg = 30; break;
        case Color::red:  fg = 31; break;
        case Color::grn:  fg = 32; break;
        case Color::ylw:  fg = 33; break;
        case Color::blu:  fg = 34; break;
        case Color::mag:  fg = 35; break;
        case Color::cyn:  fg = 36; break;
        case Color::wht:  fg = 37; break;

        case Color::gry:  fg = 90; break;
        case Color::_red: fg = 91; break;
        case Color::_grn: fg = 92; break;
        case Color::_ylw: fg = 93; break;
        case Color::_blu: fg = 94; break;
        case Color::_mag: fg = 95; break;
        case Color::_cyn: fg = 96; break;
        case Color::_wht: fg = 97; break;
    }

    std::cout << "\033[" << bg << ";" << fg << "m";
}

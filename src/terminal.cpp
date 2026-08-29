#include "terminal.h"

#include <cstdio>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

namespace {
    bool readByteWithTimeout(unsigned char& byte);
}

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void show(bool visible) {
    std::cout << (visible ? "\033[?25h" : "\033[?25l");
}

int getch() {
    termios oldSettings{};
    termios newSettings{};

    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));

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

void restoreTerminal() {
    std::cout
        << "\033[0m"
        << "\033[?25h"
        << "\033[?1049l"
        << std::flush;
}

std::optional<TerminalSize> getTerminalSize() {
    winsize windowSize{};

    if (
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize) == -1 ||
        windowSize.ws_col == 0 ||
        windowSize.ws_row == 0
    ) {
        return std::nullopt;
    }

    return TerminalSize{
        .width = static_cast<int>(windowSize.ws_col),
        .height = static_cast<int>(windowSize.ws_row)
    };
}

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void enterAlternateScreen() {
    std::cout
        << "\033[?1049h"
        << "\033[2J"
        << "\033[H"
        << std::flush;
}

void leaveAlternateScreen() {
    std::cout << "\033[?1049l";
}

int getKey() {
    termios originalSettings{};

    if (tcgetattr(STDIN_FILENO, &originalSettings) == -1) {
        return EOF;
    }

    termios rawSettings = originalSettings;

    rawSettings.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));

    rawSettings.c_cc[VMIN] = 1;
    rawSettings.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &rawSettings) == -1) {
        return EOF;
    }

    std::cout << std::flush;

    unsigned char first{};
    int result = EOF;

    if (read(STDIN_FILENO, &first, 1) == 1) {
        result = static_cast<int>(first);

        if (first == Key::Escape) {
            unsigned char second{};

            if (!readByteWithTimeout(second)) {
                result = Key::Escape;
            }
            else if (second != '[') {
                result = Key::Escape;
            }
            else {
                unsigned char third{};

                if (!readByteWithTimeout(third)) {
                    result = Key::Escape;
                }
                else {
                    switch (third) {
                        case 'A':
                            result = Key::ArrowUp;
                            break;

                        case 'B':
                            result = Key::ArrowDown;
                            break;

                        case 'C':
                            result = Key::ArrowRight;
                            break;

                        case 'D':
                            result = Key::ArrowLeft;
                            break;

                        default:
                            result = Key::Escape;
                            break;
                    }
                }
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &originalSettings);

    return result;
}

namespace {
    constexpr int escapeSequenceTimeoutMilliseconds = 50;

    bool readByteWithTimeout(unsigned char& byte) {
        pollfd input{.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};

        const int pollResult = poll(&input, 1, escapeSequenceTimeoutMilliseconds);

        if (pollResult <= 0 ||(input.revents & POLLIN) == 0) {
            return false;
        }

        return read(STDIN_FILENO, &byte, 1) == 1;
    }
}

#include <iostream>
#include <cmath>

#include "box.h"
#include "terminal.h"

namespace {
bool isValid(const Box& box);
void drawSurface(const Box& box);
void drawOutline(const Box& box);
void drawTitle(const Box& box, int width);
}

void initialize(Box& box, const IntRectangle& geometry, const std::string& title, const std::string& status) {
    box.geometry = geometry;
    box.fillChar = ' ';
    box.fillColors = { Color::_wht, Color::gry };
    box.outlineStyle = BoxOutlineStyle::SingleLine;
    box.outlineColors = { Color::gry, Color::_wht };
    box.optionalOutlineUniformChar = ' ';
    box.title = title;
    box.textColors = { Color::_wht, Color::blk };
    box.status = status;
    box.statusColors = { Color::red, Color::gry };

}

namespace {
bool isValid(const Box& box) {
    if (getHeight(box.geometry) < 3 || getWidth(box.geometry) < 3) return false;
    
    if (box.fillChar <= 31 || box.fillChar == 127) return false;
    
    if (box.outlineStyle == BoxOutlineStyle::Uniform) 
        if (box.optionalOutlineUniformChar <= 31 || box.optionalOutlineUniformChar == 127) 
            return false;
  
    return true;
}

void drawSurface(const Box& box) {
    if (!isValid(box)) return;

    int width = getWidth(box.geometry), height = getHeight(box.geometry);

    setColors(box.fillColors);
    for (int y = 0; y < height - 1; ++y) {
        gotoxy(box.geometry.topLeft.x + 1, box.geometry.topLeft.y + 1 + y);

        for (int x = 0; x < width - 1; ++x) {
            std::cout << " ";
        }
    }
}

void drawOutline(const Box& box) {
    if (!isValid(box)) return;

    int width = getWidth(box.geometry), height = getHeight(box.geometry);

    setColors(box.outlineColors);
    for (int x{}; x < width + 1; ++x) {
        gotoxy(box.geometry.topLeft.x + x, box.geometry.topLeft.y); std::cout << " ";
        gotoxy(box.geometry.topLeft.x + x, box.geometry.topLeft.y + height); std::cout << " ";
    }
    for (int y{}; y < height + 1; ++y) {
        gotoxy(box.geometry.topLeft.x, box.geometry.topLeft.y + y); std::cout << " ";
        gotoxy(box.geometry.topLeft.x + width, box.geometry.topLeft.y + y); std::cout << " ";
    }
    drawTitle(box, width);
}

void drawTitle(const Box& box, int width) {
    setColors(box.outlineColors);
    gotoxy(static_cast<int>(box.geometry.topLeft.x + std::round((width)/ 2.0) - std::round(static_cast<double>(box.title.length())/2.0)), box.geometry.topLeft.y);
    std::cout << box.title;
}
}

void draw(const Box& box) {
    drawSurface(box);
    drawOutline(box);
}

void draw(const Box box[], std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        draw(box[i]);
    }
}

void draw() {
    setColors({ Color::wht, Color::wht });

    for (int x{}; x < 120; ++x) {
        for (int y{}; y < 30; ++y) {
            gotoxy(x, y); std::cout << " ";
        }
    }
}

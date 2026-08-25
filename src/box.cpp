#include <iostream>
#include <cmath>

#include "box.h"
#include "application.h"
#include "terminal.h"

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

bool isValid(const Box& box) {
    if (getHeight(box.geometry) < 3 || getWidth(box.geometry) < 3) return false;
    
    if (box.fillChar <= 31 || box.fillChar == 127) return false;
    
    if (box.outlineStyle == BoxOutlineStyle::Uniform) 
        if (box.optionalOutlineUniformChar <= 31 || box.optionalOutlineUniformChar == 127) 
            return false;
  
    return true;
}

IntPoint boxToScreenCoord(const IntPoint& coord, const Box& box) {
    return  { box.geometry.topLeft.x + coord.x,
              box.geometry.topLeft.y + coord.y };
}

IntPoint screenToBoxCoord(const IntPoint& coord, const Box& box) {
    return { coord.x - box.geometry.topLeft.x,
             coord.y - box.geometry.topLeft.y };
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
    gotoxy(box.geometry.topLeft.x + std::round((width)/ 2.0) - std::round(box.title.length()/2.0), box.geometry.topLeft.y); 
    std::cout << box.title;
}

void draw(const Box& box) {
    drawSurface(box);
    drawOutline(box);
}

void draw(Box box[]) {
    for (int i{}; i <= 2; ++i) {
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


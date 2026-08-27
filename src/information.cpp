#include <iostream>
#include <iomanip>
#include <iterator>
#include <string_view>
#include <algorithm>

#include "information.h"
#include "terminal.h"
#include "curveCollection.h"

namespace {
void drawInformationMain(const Application& application);
void drawInformationVisualization(const Application& application);
void drawInformationCurve(const Application& application);
std::string toStringCurveType(CurveType curve);
}


void drawInformationBox(const Application& application) {
    if (application.currentMenu == Mode::HomeMenu) {
        drawInformationMain(application);
    }
    else if (application.currentMenu == Mode::InteractiveView) {
        drawInformationVisualization(application);
    }
    else if (application.currentMenu == Mode::CurveMenu) {
        drawInformationCurve(application);
    }
}

namespace {
void drawInformationMain(const Application& application) {
    setColors(application.box[2].textColors);
    IntPoint topLeft = application.box[2].geometry.topLeft;

    constexpr std::string_view label[] = {
        " About",
        " Functions",
        " Get started"
    };

    const std::string_view info[] = {
        "Interactive mathematical function grapher",
        "Trigonometric, polynomial, exponential, logarithmic",
        "Press V to explore or C to edit curves"
    };

    for (std::size_t y = 0; y < std::size(label); ++y) {
        gotoxy(topLeft.x + 1, topLeft.y + 1 + static_cast<int>(y));
        std::cout << std::left << std::setw(14) << label[y] << ": " << info[y];
    }
}

void drawInformationVisualization(const Application& application) {
    setColors(application.box[2].textColors);
    
    int halfWidth = getWidth(application.box[0].geometry) / 2,
        halfHeight = getHeight(application.box[0].geometry) / 2;
    
    IntPoint topLeft = application.box[2].geometry.topLeft,
             offset = application.graph.centerOffset,
             center = getCenter(application.graph.box.geometry);

    RealPoint realCenter = boxToGraphCoord(center, application.graph),
              zoom = { application.graph.zoomXFactor, application.graph.zoomYFactor },
              topLeftValue = boxToGraphCoord({ center.x - halfWidth, center.y - halfHeight }, application.graph),
              bottomRightValue = boxToGraphCoord({ center.x + halfWidth, center.y + halfHeight }, application.graph);

    std::string label[] = { " X-axis", " Y-axis", " Offset", " Center", " Zoom" };

    const double minimumX = std::min(topLeftValue.x, bottomRightValue.x);
    const double maximumX = std::max(topLeftValue.x, bottomRightValue.x);

    const double minimumY = std::min(topLeftValue.y, bottomRightValue.y);
    const double maximumY = std::max(topLeftValue.y, bottomRightValue.y);

    std::string info[] =  {
        toString({minimumX, maximumX}, 2, "[", ", ", "]"),
        toString({minimumY, maximumY}, 2, "[", ", ", "]"),
        toString(offset),
        toString(realCenter),
        toString(zoom, 2, "", " X ", "")
    };

    for (std::size_t y = 0; y < std::size(label); ++y) {
        gotoxy(topLeft.x + 1, topLeft.y + 1 + static_cast<int>(y));
        std::cout << std::left << std::setw(14) << label[y] << ": " << info[y];
    }
}

    void drawInformationCurve(const Application& application) {
    setColors(application.box[2].textColors);

    const CurveCollection::CurveWindow curves =
        application.curves.currentWindow();

    clearBoxContent(application.box[2]);

    for (std::size_t i = 0; i < curves.size(); ++i) {
        gotoxy(
            application.box[2].geometry.topLeft.x + 1,
            application.box[2].geometry.topLeft.y + 1
                + static_cast<int>(i)
        );

        const int offset = static_cast<int>(i) - 2;

        if (offset == 0) {
            std::cout << std::setw(5) << "  >>>" << " : ";
        }
        else if (offset < 0) {
            std::cout << " " << std::setw(4) << offset << " : ";
        }
        else {
            std::cout << " +" << std::setw(3) << offset << " : ";
        }

        const Curve* curve = curves[i];

        if (curve != nullptr) {
            std::cout
                << std::right << std::setw(11)
                << toStringCurveType(curve->curveType)
                << std::left << " [" << curve->curveChar << "] | "
                << toString(*curve, 2);
        }
    }
}

std::string toStringCurveType(CurveType curve) {
    switch (curve) {
    case CurveType::None:
        return " ";
    case CurveType::Sinus:
        return "sinus";
    case CurveType::Cosinus:
        return "cosinus";
    case CurveType::Tangent:
        return "tangent";
    case CurveType::Polynomial:
        return "polynomial";
    case CurveType::Exponential:
        return "exponential";
    case CurveType::Logarithmic:
        return "logarithmic";
    }

    return " ";
}
}

std::string toStringCurveTypeShort(CurveType curve) {
    switch (curve) {
    case CurveType::None:
        return " ";
    case CurveType::Sinus:
        return "sin";
    case CurveType::Cosinus:
        return "cos";
    case CurveType::Tangent:
        return "tan";
    case CurveType::Polynomial:
        return "pol";
    case CurveType::Exponential:
        return "exp";
    case CurveType::Logarithmic:
        return "log";
    }

    return " ";
}

void clearBoxContent(const Box& box) {
	IntPoint topLeft = box.geometry.topLeft;
	IntPoint bottomRight = box.geometry.bottomRight;

	setColors(box.fillColors);

	for (int y = topLeft.y + 1; y <= bottomRight.y; ++y) {
		gotoxy(topLeft.x + 1, y);
		for (int x = topLeft.x + 1; x <= bottomRight.x; ++x) {
			std::cout << " ";
		}
	}
}


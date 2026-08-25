#include <iostream>
#include <iomanip>
#include <iterator>

#include "information.h"
#include "terminal.h"

static void drawInformationMain(const Application& application);
static void drawInformationVisualization(const Application& application);
static void drawInformationCurve(const Application& application);
static std::string toStringCurveType(CurveType curve);


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

static void drawInformationMain(const Application& application) {
    setColors(application.box[2].textColors);
    IntPoint topLeft = application.box[2].geometry.topLeft;

    constexpr std::string label[] = {
        " About",
        " Functions",
        " Get started"
    };

    const std::string info[] = {
        "Interactive mathematical function grapher",
        "Trigonometric, polynomial, exponential, logarithmic",
        "Press V to explore or C to edit curves"
    };

    for (int y = 0; y < std::size(label); ++y) {
        gotoxy(topLeft.x + 1, topLeft.y + 1 + y);
        std::cout << std::left << std::setw(14) << label[y] << ": " << info[y];
    }
}

static void drawInformationVisualization(const Application& application) {
    setColors(application.box[2].textColors);
    
    int halfWidth = getWidth(application.box[0].geometry) / 2,
        halfHeight = getHeight(application.box[0].geometry) / 2;
    
    IntPoint topLeft = application.box[2].geometry.topLeft,
             offset = application.graph.centerOffset,
             center = getCenter(application.graph.box.geometry);

    RealPoint realCenter = boxToGraphCoord(center, application.graph),
              zoom = { application.graph.zoomXFactor, application.graph.zoomYFactor },
              minValue = boxToGraphCoord({ center.x - halfWidth, center.y - halfHeight }, application.graph),
              maxValue = boxToGraphCoord({ center.x + halfWidth, center.y + halfHeight }, application.graph);

    std::string label[] = { " X-axis", " Y-axis", " Offset", " Center", " Zoom" };
    std::string info[] =  {
        toString({minValue.x, maxValue.x}, 2, "[", ", ", "]"),
        toString({minValue.y, maxValue.y}, 2, "[", ", ", "]"),
        toString(offset),
        toString(realCenter),
        toString(zoom, 2, "", " X ", "")
    };

    for (int y{}; y < std::size(label); ++y) {
        gotoxy(topLeft.x + 1, topLeft.y + 1 + y);
        std::cout << std::left << std::setw(14) << label[y] << ": " << info[y];
    }
}

static void drawInformationCurve(const Application& application) {
    setColors(application.box[2].textColors);
    
    IntPoint topLeft = application.box[2].geometry.topLeft;
    Item* item[] = { nullptr, nullptr, application.currentCurve, nullptr, nullptr };

    if (application.currentCurve && application.currentCurve->prev) {
        item[1] = application.currentCurve->prev;
        if (item[1]->prev)
            item[0] = item[1]->prev;
    }

    if (application.currentCurve && application.currentCurve->next) {
        item[3] = application.currentCurve->next;
        if (item[3]->next)
            item[4] = item[3]->next;
    }

    clearBoxContent(application.box[2]);
    
    for (int i{}; i < sizeof(item) / sizeof(item[0]); ++i) {
        gotoxy(application.box[2].geometry.topLeft.x + 1, application.box[2].geometry.topLeft.y + 1 + i);

        if (i == 2)
            std::cout << std::setw(5) << "  >>>" << " : ";
        else if (i - 2 < 0)
            std::cout << " " << std::setw(4) << (i - 2) << " : ";
        else
            std::cout << " +" << std::setw(3) << (i - 2) << " : ";

        if (item[i])

            std::cout << std::right << std::setw(10) << toStringCurveType(item[i]->curve.curveType)
            << std::left << " [" << item[i]->curve.curveChar << "] | " << toString(item[i]->curve, 2);
    }
}

static std::string toStringCurveType(CurveType curve) {
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
        return "logrithmic";
    }

    return " ";
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



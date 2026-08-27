#include <iostream>

#include "terminal.h"
#include "graph.h"

void initialize(Graph& graph, const Box& box, double zoomFactor) {
	graph.box = box;
	graph.centerOffset = { 0,0 };
	graph.zoomXFactor = zoomFactor;
	graph.zoomYFactor = zoomFactor;
    graph.axisColor = Color::blk;
}

IntPoint graphToBoxCoord(const RealPoint& coord, const Graph& graph) {
    RealPoint center = getRealCenter(graph.box.geometry);

    return { static_cast<int>(center.x + graph.centerOffset.x + coord.x * graph.zoomXFactor),
			 static_cast<int>(center.y + graph.centerOffset.y - coord.y * graph.zoomYFactor) };
}

RealPoint boxToGraphCoord(const IntPoint& coord, const Graph& graph) {
    RealPoint center = getRealCenter(graph.box.geometry);

    return{ (coord.x - (center.x + graph.centerOffset.x)) / graph.zoomXFactor,
			-(coord.y - (center.y + graph.centerOffset.y)) / graph.zoomYFactor };
}

void drawAxis(const Graph& graph) {
    const IntPoint center = getCenter(graph.box.geometry);
    const IntPoint topRight = getTopRight(graph.box.geometry);
    const IntPoint bottomLeft = getBottomLeft(graph.box.geometry);

    const int drawXAxis = center.x + graph.centerOffset.x;
    const int drawYAxis = center.y + graph.centerOffset.y;

    setColors({ graph.box.fillColors.background, graph.axisColor });

    if (drawYAxis >= topRight.y + 1 && drawYAxis <= bottomLeft.y - 1) {
        for (int x = bottomLeft.x + 1; x <= topRight.x - 1; ++x) {
            gotoxy(x, drawYAxis + 1);
            std::cout << (x == topRight.x - 1 ? ">" : "-");
        }
    }

    if (drawXAxis >= bottomLeft.x + 1 && drawXAxis <= topRight.x - 1) {
        for (int y = topRight.y + 1; y <= bottomLeft.y; ++y) {
            gotoxy(drawXAxis + 1, y);
            std::cout << (y == topRight.y + 1 ? "A" : "|");
        }
    }
}

void zoomIn(Graph& graph) {
    graph.zoomXFactor += graph.zoomXFactor * 0.10;
    graph.zoomYFactor += graph.zoomYFactor * 0.10;
}

void zoomInX(Graph& graph) { graph.zoomXFactor += graph.zoomXFactor * 0.10; }

void zoomInY(Graph& graph) { graph.zoomYFactor += graph.zoomYFactor * 0.10; }

void zoomOut(Graph& graph) {
    graph.zoomXFactor -= graph.zoomXFactor * 0.10;
    graph.zoomYFactor -= graph.zoomYFactor * 0.10;
}
void zoomOutX(Graph& graph) { graph.zoomXFactor -= graph.zoomXFactor * 0.10; }
void zoomOutY(Graph& graph) { graph.zoomYFactor -= graph.zoomYFactor * 0.10; }

/*
void pan(Graph& graph, const IntPoint& translation) {

}
*/

void panLeft(Graph& graph) { graph.centerOffset.x -= 1; }

void panUp(Graph& graph) { graph.centerOffset.y -= 1; }

void panRight(Graph& graph) { graph.centerOffset.x += 1;}

void panDown(Graph& graph) { graph.centerOffset.y += 1; }

namespace {
void resetZoom(Graph& graph) { graph.zoomXFactor = graph.zoomYFactor = 5.0; }

void resetPan(Graph& graph) { graph.centerOffset = { 0,0 }; }
}

void reset(Graph& graph) {
    resetPan(graph);
    resetZoom(graph);
}

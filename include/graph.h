#pragma once

#include "point.h"
#include "box.h"

struct Graph {
	Box box;
	IntPoint centerOffset;
	double zoomXFactor;
	double zoomYFactor;
	Color axisColor;
};


void initialize(Graph& graph, const Box& box, double zoomFactor = 5.0);

IntPoint graphToBoxCoord(const RealPoint& coord, const Graph& graph);
RealPoint boxToGraphCoord(const IntPoint& coord, const Graph& graph);

void drawAxis(const Graph& graph);

void zoomIn(Graph& graph);
void zoomInX(Graph& graph);
void zoomInY(Graph& graph);
void zoomOut(Graph& graph);
void zoomOutX(Graph& graph);
void zoomOutY(Graph& graph);

void pan(Graph& graph, const IntPoint& translation);
void panLeft(Graph& graph);
void panUp(Graph& graph);
void panRight(Graph& graph);
void panDown(Graph& graph);

void resetZoom(Graph& graph);
void resetPan(Graph& graph);
void reset(Graph& graph);
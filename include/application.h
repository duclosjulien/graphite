#pragma once

#include <cstddef>

#include "curveCollection.h"
#include "graph.h"
#include "menu.h"

constexpr std::size_t boxSize = 3;
constexpr std::size_t menuSize = 3;

enum class Mode { HomeMenu, InteractiveView, CurveMenu};

struct Application {
	bool applicationIsRunning; 
	int width, height, layoutOffset;

	Box box[boxSize];
	Menu menu[menuSize];
	Graph graph;
	
	Mode currentMenu;

	bool showAllCurves;
	CurveCollection curves;
};

void initialize(Application& application, int width = 120, int height = 30);

void run(Application& application);

void finalize(Application& application);

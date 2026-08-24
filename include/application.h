#pragma once

#include "curvelist.h"
#include "actions.h"
#include "menu.h"

const int boxSize = 3, menuSize = 3;

enum class Mode { HomeMenu, InteractiveView, CurveMenu};

struct Application {
	bool applicationIsRunning; 
	int width, height, layoutOffset;

	Box box[boxSize];
	Menu menu[menuSize];
	Graph graph;
	
	Mode currentMenu;

	bool showAllCurves;
	CurvesList curves;
	Item* currentCurve;
};

void initialize(Application& application, int width = 120, int height = 30);

void run(Application& application);

void finalize(Application& application);

void draw(const Application& application);


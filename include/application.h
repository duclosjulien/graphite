#pragma once

#include <cstddef>
#include <optional>

#include "curveCollection.h"
#include "graph.h"
#include "menu.h"

constexpr std::size_t boxSize = 3;
constexpr std::size_t menuSize = 3;
inline constexpr int minimumTerminalWidth = 118;
inline constexpr int minimumTerminalHeight = 29;

enum class Mode { HomeMenu, InteractiveView, CurveMenu};

struct Application {
	bool applicationIsRunning; 
	int width, height, layoutOffset;
	std::optional<std::size_t> selectedParameterIndex = std::nullopt;

	Box box[boxSize];
	Menu menu[menuSize];
	Graph graph;
	
	Mode currentMenu;

	bool showAllCurves;
	CurveCollection curves;
};

void initialize(Application& application, int width, int height);

void run(Application& application);

void finalize(Application& application);

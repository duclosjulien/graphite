#pragma once

#include <cstddef>
#include <string>

#include "action.h"

extern const std::size_t sizeActionHome;
extern const std::string homeName[];
extern const Action homeAction[];
extern const char homeKey[];

extern const std::size_t sizeActionVisualization;
extern const std::string visualizationName[];
extern const Action visualizationAction[];
extern const char visualizationKey[];

extern const std::size_t sizeActionCurve;
extern const std::string curveName[];
extern const Action curveAction[];
extern const char curveKey[];

extern const std::size_t sizeHiddenActionCurve;
extern const HiddenAction curveHiddenAction[];
extern const char hiddenCurveKey[];

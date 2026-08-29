#pragma once

#include <cstddef>
#include <string>

#include "action.h"

extern const std::size_t sizeActionHome;
extern const std::string homeName[];
extern const Action homeAction[];
extern const int homeKey[];

extern const std::size_t sizeActionVisualization;
extern const std::string visualizationName[];
extern const Action visualizationAction[];
extern const int visualizationKey[];

extern const std::size_t sizeActionCurve;
extern const std::string curveName[];
extern const Action curveAction[];
extern const int curveKey[];

extern const std::size_t sizeHiddenActionCurve;
extern const HiddenAction curveHiddenAction[];
extern const int hiddenCurveKey[];

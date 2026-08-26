#pragma once

#include <string>

#include "application.h"
#include "box.h"
#include "curve.h"

void drawInformationBox(const Application& application);

std::string  toStringCurveTypeShort(CurveType curve);

void clearBoxContent(const Box& box);

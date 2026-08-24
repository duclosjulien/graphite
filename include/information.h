#pragma once

#include "box.h"
#include "graph.h"
#include "application.h"

const int informationSizeHome = 3, 
		  informationSizeVisualization = 5,
	      informationSizeCurve = 5;

void drawInformationBox(const Application& application);

std::string  toStringCurveTypeShort(CurveType curve);

void clearBoxContent(const Box& box);


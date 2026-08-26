#pragma once

#include <cstddef>

#include "curve.h"
#include "graph.h"

struct Item {
	Curve curve; 
	Item* prev, * next;
};

struct CurvesList {
	Item* first, * last;
	std::size_t size;
};

void initialize(CurvesList& list);

Item* insert(CurvesList& list, Item* item, const Curve& curve);

void erase(CurvesList& list, const Item* item);

void clear(CurvesList& list);

void drawForward(const CurvesList& list, const Graph& graph);

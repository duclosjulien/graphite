#pragma once

#include "curve.h"

struct Item {
	Curve curve; 
	Item* prev, * next;
};

struct CurvesList {
	Item* first, * last;
	size_t size;
};

void initialize(CurvesList& list);

void pushLast(CurvesList& list, const Curve& curve);

Item* insert(CurvesList& list, Item* item, const Curve& curve);

void erase(CurvesList& list, const Item* item);

void clear(CurvesList& list);

void drawForward(const CurvesList& list, const Graph& graph);

void drawBackward(const CurvesList& list, const Graph& graph);

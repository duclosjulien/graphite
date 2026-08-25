#include "curvelist.h"

void initialize(CurvesList& list) {
	list.first = list.last = nullptr;
	list.size = 0;
}

void pushLast(CurvesList& list, const Curve& curve) {
    Item* item = new Item{ curve, list.last, nullptr };

    if (list.last)
        list.last = list.last->next = item;
    else
        list.first = list.last = item;

    ++list.size;
}

Item* insert(CurvesList& list, Item* pos, const Curve& curve) {
    if (pos == nullptr) {
        pushLast(list, curve);
        return list.last;  
    }

    Item* item = new Item{ curve, pos, pos->next };

    if (pos->next)
        pos->next->prev = item;
    else
        list.last = item;

    pos->next = item;

    ++list.size;
    return item;
}

void erase(CurvesList& list, const Item* item) {
    if (!item) {
        return;
    }

    if (item->next)
        item->next->prev = item->prev;
    else
        list.last = item->prev;

    if (item->prev)
        item->prev->next = item->next;
    else
        list.first = item->next;

    delete item;
    --list.size;
}

void clear(CurvesList& list) {
    while (list.first) {
        erase(list, list.first);
    }
}

void drawForward(const CurvesList& list, const Graph& graph)  {
    Item* item = list.first;
    while (item) {
        draw(item->curve, graph);
        item = item->next;
    }
}

void drawBackward(const CurvesList& list, const Graph& graph)  {
    Item* item = list.last;
    while (item) {
        draw(item->curve, graph);
        item = item->prev;
    }
}

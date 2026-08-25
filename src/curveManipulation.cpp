#include "curveManipulation.h"

void selectNextCurve(Application& application) {
    if (application.currentCurve && application.currentCurve->next)
        application.currentCurve = application.currentCurve->next;
}

void selectPreviousCurve(Application& application) {
    if (application.currentCurve && application.currentCurve->prev)
        application.currentCurve = application.currentCurve->prev;
}

void selectFirstCurve(Application& application) {
    if (application.curves.first)
        application.currentCurve = application.curves.first;
}

void selectLastCurve(Application& application) {
    if (application.curves.last)
        application.currentCurve = application.curves.last;
}

void removeCurrentCurve(Application& application) {
    if (application.currentCurve) {
        Item* item = application.currentCurve;

        if (item->next)
            application.currentCurve = item->next;
        else if (item->prev)
            application.currentCurve = item->prev;
        else
            application.currentCurve = nullptr;

        erase(application.curves, item);
    }
}
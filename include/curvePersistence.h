#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "curve.h"
#include "curveCollection.h"

struct CurveLoadResult {
    std::vector<Curve> curves;
    std::string error;

    [[nodiscard]] bool succeeded() const {
        return error.empty();
    }
};

CurveLoadResult loadCurves(std::istream& input);

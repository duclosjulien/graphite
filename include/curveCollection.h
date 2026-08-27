#pragma once

#include <cstddef>
#include <list>
#include <array>

#include "curve.h"

class CurveCollection {
public:
    CurveCollection();

    CurveCollection(const CurveCollection&) = delete;
    CurveCollection& operator=(const CurveCollection&) = delete;
    CurveCollection(CurveCollection&&) = delete;
    CurveCollection& operator=(CurveCollection&&) = delete;

    using CurveWindow = std::array<const Curve*, 5>;
    using const_iterator = std::list<Curve>::const_iterator;

    const_iterator begin() const;
    const_iterator end() const;

    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::size_t size() const;

    Curve& insertAfterCurrent(const Curve& curve);
    bool removeCurrent();

    bool selectNext();
    bool selectPrevious();
    bool selectFirst();
    bool selectLast();
    [[nodiscard]] CurveWindow currentWindow() const;

    [[nodiscard]] Curve* current();
    [[nodiscard]] const Curve* current() const;

    void clear();

private:
    std::list<Curve> curves_;
    std::list<Curve>::iterator current_;
};
#include <iterator>

#include "curveCollection.h"


CurveCollection::CurveCollection()
: current_(curves_.end()) {
}

CurveCollection::const_iterator CurveCollection::begin() const {
    return curves_.cbegin();
}

CurveCollection::const_iterator CurveCollection::end() const {
    return curves_.cend();
}

bool CurveCollection::empty() const {
    return curves_.empty();
}

std::size_t CurveCollection::size() const {
    return curves_.size();
}

const Curve* CurveCollection::current() const {
    if (current_ == curves_.end()) {
        return nullptr;
    }

    return &(*current_);
}

Curve* CurveCollection::current() {
    if (current_ == curves_.end()) {
        return nullptr;
    }

    return &(*current_);
}

bool CurveCollection::selectNext() {
    if (current_ == curves_.end()) {
        return false;
    }

    auto next = std::next(current_);

    if (next == curves_.end()) {
        return false;
    }

    current_ = next;
    return true;
}

bool CurveCollection::selectPrevious() {
    if (current_ == curves_.end() ||current_ == curves_.begin()) {
        return false;
    }

    --current_;
    return true;
}

bool CurveCollection::selectFirst() {
    if (curves_.empty()) {
        return false;
    }

    current_ = curves_.begin();
    return true;
}

bool CurveCollection::selectLast() {
    if (curves_.empty()) {
        return false;
    }

    current_ = std::prev(curves_.end());
    return true;
}

Curve& CurveCollection::insertAfterCurrent(const Curve& curve) {
    if (current_ == curves_.end()) {
        current_ = curves_.insert(curves_.end(), curve);
    } else {
        current_ = curves_.insert(std::next(current_), curve);
    }
    return *current_;
}

bool CurveCollection::removeCurrent() {
    if (current_ == curves_.end()) {
        return false;
    }

    current_ = curves_.erase(current_);

    if (current_ == curves_.end() && !curves_.empty()) {
        current_ = std::prev(curves_.end());
    }

    return true;
}

void CurveCollection::clear() {
    curves_.clear();
    current_ = curves_.end();
}

CurveCollection::CurveWindow CurveCollection::currentWindow() const {
    CurveWindow curves{};

    if (current_ == curves_.end()) {
        return curves;
    }

    curves[2] = &*current_;

    const_iterator previous = current_;

    for (std::size_t index = 2; index > 0;) {
        if (previous == curves_.cbegin()) {
            break;
        }

        --previous;
        --index;
        curves[index] = &*previous;
    }

    const_iterator next = current_;

    for (std::size_t index = 3; index < curves.size(); ++index) {
        ++next;

        if (next == curves_.cend()) {
            break;
        }

        curves[index] = &*next;
    }

    return curves;
}
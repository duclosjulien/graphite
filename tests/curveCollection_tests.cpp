#include <catch2/catch_test_macros.hpp>
#include <string>

#include "curveCollection.h"

TEST_CASE("curve collection starts empty") {
    const CurveCollection curves;

    REQUIRE(curves.empty());
    REQUIRE(curves.size() == 0);
    REQUIRE(curves.current() == nullptr);
}

TEST_CASE("inserting the first curve selects it") {
    CurveCollection curves;

    Curve curve = createSinus();
    curve.curveChar = 'A';

    Curve& inserted = curves.insertAfterCurrent(curve);

    REQUIRE_FALSE(curves.empty());
    REQUIRE(curves.size() == 1);
    REQUIRE(curves.current() == &inserted);
    REQUIRE(curves.current()->curveChar == 'A');
}

TEST_CASE("new curves are inserted after the current curve") {
    CurveCollection curves;

    Curve curveA = createSinus();
    curveA.curveChar = 'A';

    Curve curveB = createCosinus();
    curveB.curveChar = 'B';

    Curve curveC = createTangent();
    curveC.curveChar = 'C';

    curves.insertAfterCurrent(curveA); // [A], current A
    curves.insertAfterCurrent(curveB); // [A, B], current B

    REQUIRE(curves.selectPrevious());  // Current A

    curves.insertAfterCurrent(curveC); // [A, C, B], current C

    std::string order;

    for (const Curve& curve : curves) {
        order += curve.curveChar;
    }

    REQUIRE(order == "ACB");

    REQUIRE(curves.size() == 3);
    REQUIRE(curves.current()->curveChar == 'C');

    REQUIRE(curves.selectPrevious());
    REQUIRE(curves.current()->curveChar == 'A');

    REQUIRE(curves.selectNext());
    REQUIRE(curves.current()->curveChar == 'C');

    REQUIRE(curves.selectNext());
    REQUIRE(curves.current()->curveChar == 'B');

    REQUIRE_FALSE(curves.selectNext());
    REQUIRE(curves.current()->curveChar == 'B');
}

TEST_CASE("removing a middle curve selects the next curve") {
    CurveCollection curves;

    Curve curveA = createSinus();
    curveA.curveChar = 'A';

    Curve curveB = createCosinus();
    curveB.curveChar = 'B';

    Curve curveC = createTangent();
    curveC.curveChar = 'C';

    curves.insertAfterCurrent(curveA);
    curves.insertAfterCurrent(curveB);
    curves.insertAfterCurrent(curveC);

    REQUIRE(curves.selectPrevious());
    REQUIRE(curves.current()->curveChar == 'B');

    REQUIRE(curves.removeCurrent());

    REQUIRE(curves.size() == 2);
    REQUIRE(curves.current() != nullptr);
    REQUIRE(curves.current()->curveChar == 'C');

    REQUIRE(curves.selectPrevious());
    REQUIRE(curves.current()->curveChar == 'A');
}

TEST_CASE("removing the last curve selects the previous curve") {
    CurveCollection curves;

    Curve curveA = createSinus();
    curveA.curveChar = 'A';

    Curve curveB = createCosinus();
    curveB.curveChar = 'B';

    curves.insertAfterCurrent(curveA);
    curves.insertAfterCurrent(curveB);

    REQUIRE(curves.current()->curveChar == 'B');
    REQUIRE(curves.removeCurrent());

    REQUIRE(curves.size() == 1);
    REQUIRE(curves.current() != nullptr);
    REQUIRE(curves.current()->curveChar == 'A');
}

TEST_CASE("removing the only curve leaves no selection") {
    CurveCollection curves;

    curves.insertAfterCurrent(createSinus());

    REQUIRE(curves.removeCurrent());

    REQUIRE(curves.empty());
    REQUIRE(curves.size() == 0);
    REQUIRE(curves.current() == nullptr);

    REQUIRE_FALSE(curves.removeCurrent());
    REQUIRE_FALSE(curves.selectNext());
    REQUIRE_FALSE(curves.selectPrevious());
    REQUIRE_FALSE(curves.selectFirst());
    REQUIRE_FALSE(curves.selectLast());
}

TEST_CASE("removing the first curve selects the next curve") {
    CurveCollection curves;

    Curve curveA = createSinus();
    curveA.curveChar = 'A';

    Curve curveB = createCosinus();
    curveB.curveChar = 'B';

    curves.insertAfterCurrent(curveA);
    curves.insertAfterCurrent(curveB);

    REQUIRE(curves.selectFirst());
    REQUIRE(curves.current()->curveChar == 'A');

    REQUIRE(curves.removeCurrent());

    REQUIRE(curves.size() == 1);
    REQUIRE(curves.current() != nullptr);
    REQUIRE(curves.current()->curveChar == 'B');
}

TEST_CASE("clearing curves resets selection and allows reuse") {
    CurveCollection curves;

    curves.insertAfterCurrent(createSinus());
    curves.insertAfterCurrent(createCosinus());
    curves.insertAfterCurrent(createTangent());

    curves.clear();

    REQUIRE(curves.empty());
    REQUIRE(curves.size() == 0);
    REQUIRE(curves.current() == nullptr);

    Curve& inserted = curves.insertAfterCurrent(createPolynomial(2));

    REQUIRE(curves.size() == 1);
    REQUIRE(curves.current() == &inserted);
}

TEST_CASE("first and last selection respect collection boundaries") {
    CurveCollection curves;

    Curve curveA = createSinus();
    curveA.curveChar = 'A';

    Curve curveB = createCosinus();
    curveB.curveChar = 'B';

    Curve curveC = createTangent();
    curveC.curveChar = 'C';

    curves.insertAfterCurrent(curveA);
    curves.insertAfterCurrent(curveB);
    curves.insertAfterCurrent(curveC);

    REQUIRE(curves.selectFirst());
    REQUIRE(curves.current()->curveChar == 'A');

    REQUIRE_FALSE(curves.selectPrevious());
    REQUIRE(curves.current()->curveChar == 'A');

    REQUIRE(curves.selectLast());
    REQUIRE(curves.current()->curveChar == 'C');

    REQUIRE_FALSE(curves.selectNext());
    REQUIRE(curves.current()->curveChar == 'C');
}
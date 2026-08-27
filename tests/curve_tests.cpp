#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <numbers>
#include <stdexcept>

#include "curve.h"
#include "curveCollection.h"
#include "catch2/catch_approx.hpp"

TEST_CASE("createPolynomial accepts the maximum degree") {
    const Curve curve = createPolynomial(maxPolynomialDegree);

    REQUIRE(
        curve.parameterValues.size() ==
        maxPolynomialDegree + 1
    );
    REQUIRE(
        curve.parameterNames.size() ==
        maxPolynomialDegree + 1
    );
}

TEST_CASE("createPolynomial creates one coefficient per polynomial term") {
    constexpr std::size_t degree = 2;

    const Curve curve = createPolynomial(degree);

    REQUIRE(curve.curveType == CurveType::Polynomial);
    REQUIRE(curve.parameterValues.size() == degree + 1);
    REQUIRE(curve.parameterNames.size() == degree + 1);

    for (const double coefficient : curve.parameterValues) {
        REQUIRE(coefficient == 1.0);
    }
}

TEST_CASE("createPolynomial supports degree zero") {
    const Curve curve = createPolynomial(0);

    REQUIRE(curve.parameterValues.size() == 1);
    REQUIRE(curve.parameterNames.size() == 1);
}

TEST_CASE("createPolynomial rejects degrees above the maximum") {
    REQUIRE_THROWS_AS(
        createPolynomial(maxPolynomialDegree + 1),
        std::invalid_argument
    );
}

TEST_CASE("modifyParameter updates a valid parameter") {
    Curve curve = createSinus();
    const double originalValue = curve.parameterValues[0];

    modifyParameter(curve, 0.5, 0);

    REQUIRE(curve.parameterValues[0] == originalValue + 0.5);
}

TEST_CASE("modifyParameter ignores an unavailable parameter") {
    Curve curve = createSinus();
    const auto originalValues = curve.parameterValues;

    modifyParameter(curve, 0.5, curve.parameterValues.size());

    REQUIRE(curve.parameterValues == originalValues);
}

TEST_CASE("modifyParameter ignores an empty curve") {
    Curve curve{};

    REQUIRE_NOTHROW(modifyParameter(curve, 0.5, 0));
    REQUIRE(curve.parameterValues.empty());
}

TEST_CASE("modifyParameter handles four-parameter curve boundaries") {
    Curve curve = createSinus();

    modifyParameter(curve, 0.5, 3);
    REQUIRE(curve.parameterValues[3] == 0.5);

    const auto values = curve.parameterValues;
    modifyParameter(curve, 0.5, 4);
    REQUIRE(curve.parameterValues == values);
}

TEST_CASE("modifyParameter handles five-parameter curve boundaries") {
    Curve curve = createExponential();

    modifyParameter(curve, 0.5, 4);
    REQUIRE(curve.parameterValues[4] == 0.5);

    const auto values = curve.parameterValues;
    modifyParameter(curve, 0.5, 5);
    REQUIRE(curve.parameterValues == values);
}

TEST_CASE("modifyParameter handles degree-zero polynomial boundaries") {
    Curve curve = createPolynomial(0);

    modifyParameter(curve, 0.5, 0);
    REQUIRE(curve.parameterValues[0] == 1.5);

    const auto values = curve.parameterValues;
    modifyParameter(curve, 0.5, 1);
    REQUIRE(curve.parameterValues == values);
}

TEST_CASE("modifyParameter handles maximum-degree polynomial boundaries") {
    Curve curve = createPolynomial(maxPolynomialDegree);

    modifyParameter(curve, 0.5, maxPolynomialDegree);
    REQUIRE(curve.parameterValues[8] == 1.5);

    const auto values = curve.parameterValues;
    modifyParameter(curve, 0.5, maxPolynomialDegree + 1);
    REQUIRE(curve.parameterValues == values);
}

TEST_CASE("copying a curve creates independent parameter storage") {
    const Curve original = createSinus();
    Curve copy = original;

    modifyParameter(copy, 0.5, 0);

    REQUIRE(copy.parameterValues[0] != original.parameterValues[0]);
    REQUIRE(original.parameterValues[0] == 1.0);
}

TEST_CASE("inserting a curve copies independent state") {
    CurveCollection curves;

    const Curve original = createSinus();
    Curve& inserted = curves.insertAfterCurrent(original);

    modifyParameter(inserted, 0.5, 0);

    REQUIRE(original.parameterValues[0] == 1.0);
    REQUIRE(inserted.parameterValues[0] == 1.5);

    REQUIRE_FALSE(curves.empty());
    REQUIRE(curves.size() == 1);
    REQUIRE(curves.current() == &inserted);
}

TEST_CASE("process returns the mathematical sine value") {
    const Curve curve = createSinus(
        2.0, // amplitude
        1.0, // frequency
        0.0, // phase
        3.0  // offset
    );

    const double result = process(
        std::numbers::pi / 2.0,
        curve
    );

    REQUIRE(result == Catch::Approx(5.0));
}

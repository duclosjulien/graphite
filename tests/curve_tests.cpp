#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <stdexcept>

#include "curve.h"

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
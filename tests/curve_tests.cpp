#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <stdexcept>

#include "curve.h"

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
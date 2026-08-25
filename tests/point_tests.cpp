#include <catch2/catch_test_macros.hpp>

#include "point.h"

TEST_CASE("integer points convert to real points") {
    const IntPoint input{2, -3};

    const RealPoint result = toReal(input);

    REQUIRE(result.x == 2.0);
    REQUIRE(result.y == -3.0);
}
#include <catch2/catch_test_macros.hpp>

#include "application.h"
#include "rectangle.h"

[[nodiscard]] bool isTerminalSizeSupported(int width, int height) {
    return width >= minimumTerminalWidth &&
           height >= minimumTerminalHeight;
}

TEST_CASE("terminal size validation checks the minimum dimensions") {
    REQUIRE(
        isTerminalSizeSupported(
            minimumTerminalWidth,
            minimumTerminalHeight
        )
    );

    REQUIRE_FALSE(
        isTerminalSizeSupported(
            minimumTerminalWidth - 1,
            minimumTerminalHeight
        )
    );

    REQUIRE_FALSE(
        isTerminalSizeSupported(
            minimumTerminalWidth,
            minimumTerminalHeight - 1
        )
    );
}

TEST_CASE("application layout creates non-overlapping boxes") {
    Application application;

    initialize(
        application,
        minimumTerminalWidth,
        minimumTerminalHeight
    );

    const IntRectangle& graph =
        application.box[0].geometry;

    const IntRectangle& menu =
        application.box[1].geometry;

    const IntRectangle& information =
        application.box[2].geometry;

    REQUIRE(graph.bottomRight.x < menu.topLeft.x);
    REQUIRE(graph.bottomRight.y < information.topLeft.y);
    REQUIRE(menu.bottomRight.y < information.topLeft.y);

    REQUIRE(getWidth(graph) > 0);
    REQUIRE(getHeight(graph) > 0);
    REQUIRE(getWidth(menu) > 0);
    REQUIRE(getHeight(menu) > 0);
    REQUIRE(getWidth(information) > 0);
    REQUIRE(getHeight(information) > 0);
}

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "graph.h"

TEST_CASE("positive graph Y maps above the terminal center") {
    Graph graph{};
    graph.box.geometry = {{0, 0}, {20, 20}};
    graph.centerOffset = {0, 0};
    graph.zoomXFactor = 2.0;
    graph.zoomYFactor = 3.0;

    const IntPoint origin = graphToBoxCoord({0.0, 0.0}, graph);
    const IntPoint positiveY = graphToBoxCoord({0.0, 1.0}, graph);
    const IntPoint negativeY = graphToBoxCoord({0.0, -1.0}, graph);

    REQUIRE(origin.x == 10);
    REQUIRE(origin.y == 10);

    REQUIRE(positiveY.y == 7);
    REQUIRE(negativeY.y == 13);
}

TEST_CASE("box Y converts back using inverted Y and vertical zoom") {
    Graph graph{};
    graph.box.geometry = {{0, 0}, {20, 20}};
    graph.centerOffset = {0, 0};
    graph.zoomXFactor = 2.0;
    graph.zoomYFactor = 3.0;

    const RealPoint result = boxToGraphCoord({10, 7}, graph);

    REQUIRE(result.x == Catch::Approx(0.0));
    REQUIRE(result.y == Catch::Approx(1.0));
}

TEST_CASE("graph coordinates round-trip with unequal zoom and pan") {
    Graph graph{};
    graph.box.geometry = {{0, 0}, {20, 20}};
    graph.centerOffset = {2, -1};
    graph.zoomXFactor = 2.0;
    graph.zoomYFactor = 3.0;

    const RealPoint original{1.5, -2.0};
    const IntPoint boxPoint = graphToBoxCoord(original, graph);
    const RealPoint result = boxToGraphCoord(boxPoint, graph);

    REQUIRE(result.x == Catch::Approx(original.x));
    REQUIRE(result.y == Catch::Approx(original.y));
}
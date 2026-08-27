add_executable(graphite_tests
        point_tests.cpp
        curve_tests.cpp
        graph_tests.cpp
        curveCollection_tests.cpp
)

target_link_libraries(graphite_tests
        PRIVATE
        graphite_core
        Catch2::Catch2WithMain
)

graphite_enable_warnings(graphite_tests)
graphite_enable_sanitizers(graphite_tests)
include(Catch)
catch_discover_tests(graphite_tests)
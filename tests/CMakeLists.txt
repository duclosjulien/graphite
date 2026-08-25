add_executable(graphite_tests
        point_tests.cpp
)

target_link_libraries(graphite_tests
        PRIVATE
        graphite_core
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(graphite_tests)
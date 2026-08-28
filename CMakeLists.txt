cmake_minimum_required(VERSION 3.19)
project(graphite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
        GRAPHITE_WARNINGS_AS_ERRORS
        "Treat project compiler warnings as errors"
        OFF
)

option(
        GRAPHITE_ENABLE_SANITIZERS
        "Enable AddressSanitizer and UndefinedBehaviorSanitizer"
        OFF
)

function(graphite_enable_warnings target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target}
                PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wshadow
                -Wconversion
                -Wsign-conversion
        )

        if(GRAPHITE_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

function(graphite_enable_sanitizers target)
    if(
            GRAPHITE_ENABLE_SANITIZERS
            AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"
    )
        target_compile_options(${target}
                PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
        )

        target_link_options(${target}
                PRIVATE
                -fsanitize=address,undefined
        )
    endif()
endfunction()

add_library(graphite_core
        src/actions.cpp
        src/application.cpp
        src/box.cpp
        src/colors.cpp
        src/curve.cpp
        src/graph.cpp
        src/information.cpp
        src/menu.cpp
        src/point.cpp
        src/rectangle.cpp
        src/terminal.cpp
        src/curveCollection.cpp
        src/curvePersistence.cpp
)

target_include_directories(graphite_core
        PUBLIC
        include
)

add_executable(graphite
        src/main.cpp
)

target_link_libraries(graphite
        PRIVATE
        graphite_core
)

graphite_enable_warnings(graphite_core)
graphite_enable_warnings(graphite)
graphite_enable_sanitizers(graphite_core)
graphite_enable_sanitizers(graphite)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG 8b08d4d79514f45f7e4ce2a607ac9c94e920d1bb
    )

    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH
            ${catch2_SOURCE_DIR}/extras
    )

    add_subdirectory(tests)
endif()

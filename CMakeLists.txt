cmake_minimum_required(VERSION 4.3)
project(graphite)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(graphite
        include/action.h
        include/actions.h
        include/application.h
        include/box.h
        include/colors.h
        include/curve.h
        include/curvelist.h
        include/curveManipulation.h
        include/graph.h
        include/information.h
        include/menu.h
        include/point.h
        include/rectangle.h
        include/terminal.h
        src/actions.cpp
        src/application.cpp
        src/box.cpp
        src/colors.cpp
        src/curve.cpp
        src/curvelist.cpp
        src/curveManipulation.cpp
        src/graph.cpp
        src/information.cpp
        src/main.cpp
        src/menu.cpp
        src/point.cpp
        src/rectangle.cpp
        src/terminal.cpp)

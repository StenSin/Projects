cmake_minimum_required(VERSION 3.8)
project(untitled7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cmake-build-debug/pugiconfig.hpp
        cmake-build-debug/pugixml.cpp
        cmake-build-debug/pugixml.hpp
        main.cpp
        pugiconfig.hpp
        pugixml.cpp
        pugixml.hpp)

add_executable(untitled7 ${SOURCE_FILES})
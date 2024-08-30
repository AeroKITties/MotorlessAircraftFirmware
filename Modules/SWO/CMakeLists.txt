cmake_minimum_required(VERSION 3.22)

# Create a static library from the sources
add_library(swo_debug STATIC
    swo_backend.cpp
    swo_backend.hpp
    swo_debug.hpp
    swo_debug.cpp
)

# Optionally, add include directories
target_include_directories(swo_debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
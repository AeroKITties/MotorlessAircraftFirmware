cmake_minimum_required(VERSION 3.22)

# Create a static library from the sources
add_library(swo-debug STATIC
    swo-backend.cpp
    swo-backend.hpp
    swo-debug.hpp
    swo-debug.cpp
)

# Optionally, add include directories
target_include_directories(swo-debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.22)

add_library(rangefinder STATIC
    hcsr04.cpp
)

target_include_directories(rangefinder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rangefinder PUBLIC stm32cubemx)
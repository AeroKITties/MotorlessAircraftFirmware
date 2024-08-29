cmake_minimum_required(VERSION 3.22)

add_library(servo STATIC
    servo.cpp
)

target_include_directories(servo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(servo PUBLIC stm32cubemx)
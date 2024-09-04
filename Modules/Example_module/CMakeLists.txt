cmake_minimum_required(VERSION 3.22)

add_library(example_module STATIC
    example_class.cpp
    example_class_stabs.cpp
    exanple_class_filters.cpp
)

target_include_directories(example_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(example_module PUBLIC stm32cubemx)
target_link_libraries(example_module PUBLIC servo)
target_link_libraries(example_module PUBLIC bmi088_legacy)
target_link_libraries(example_module PUBLIC swo_debug)
target_link_libraries(example_module PUBLIC expanded_vector3)

target_link_libraries(example_module PUBLIC sd_card)
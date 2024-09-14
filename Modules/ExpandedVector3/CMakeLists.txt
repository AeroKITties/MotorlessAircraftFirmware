cmake_minimum_required(VERSION 3.22)

add_library(expanded_vector3 STATIC
    ExpandedVector3.cpp
)

target_include_directories(expanded_vector3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(expanded_vector3 PUBLIC stm32cubemx)
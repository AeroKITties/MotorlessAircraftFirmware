cmake_minimum_required(VERSION 3.22)

add_library(bmi088 STATIC
    bmi088.cpp
    bmi088a.cpp
    bmi088g.cpp
)

target_include_directories(bmi088 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bmi088 PUBLIC stm32cubemx Eigen3::Eigen)

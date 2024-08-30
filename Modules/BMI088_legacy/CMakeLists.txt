cmake_minimum_required(VERSION 3.22)

add_library(bmi088_legacy STATIC
    Accel.c
    Vectors.c
    IMU.c
    Gyro.c
)

target_include_directories(bmi088_legacy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bmi088_legacy PUBLIC stm32cubemx)

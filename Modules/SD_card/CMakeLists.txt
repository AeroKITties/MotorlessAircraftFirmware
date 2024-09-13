cmake_minimum_required(VERSION 3.22)

add_library(sd_card STATIC
    sd_file_handling.c
    logger.cpp
    logger_messages.cpp
)

target_include_directories(sd_card PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sd_card PUBLIC stm32cubemx)
target_link_libraries(sd_card PUBLIC swo_debug)
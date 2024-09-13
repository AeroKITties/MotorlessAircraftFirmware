#include "logger.hpp"
#include "stm32f4xx_hal.h"
#include "swo_debug.hpp"


void Logger::LogCustomMessage(std::string s) {
    cache << "CUSTOM_MSG " << HAL_GetTick() << " " << s << std::endl;
    cache_size++;
}

void Logger::LogAccelRawData(float ax, float ay, float az, float gx, float gy, float gz) {
    cache << "IMU_RAW " << HAL_GetTick() << " " << ax << " " << ay << " " << az << " " << gx << " " << gy << " " << gz
          << std::endl;
    cache_size++;
}

void Logger::LogServoOutput(float servo_elevator, float servo_ailerones){
    cache << "SERVO " << HAL_GetTick() << " " << servo_elevator << " " << servo_ailerones << std::endl;
    cache_size++;
}

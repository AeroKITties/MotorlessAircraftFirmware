#pragma once

#include <stdint.h>

#include <Eigen/Dense>

#include "bmi088_defs.hpp"
#include "bmi088a.hpp"
#include "bmi088g.hpp"
#include "spi.h"

namespace bmi088 {
class BMI088 {
   public:
    BMI088(SPI_HandleTypeDef *spi, GPIO_TypeDef *csAccelPort, uint16_t csAccelPin, GPIO_TypeDef *csGyroPort,
           uint16_t csGyroPin);

    BMI088_A accel;
    BMI088_G gyro;

    Eigen::Vector3f getAcceleration() { return accel.getAcceleration(); };

   private:
};
}  // namespace bmi088

#include "bmi088.hpp"

namespace bmi088 {

BMI088::BMI088(SPI_HandleTypeDef *spi, GPIO_TypeDef *csAccelPort, uint16_t csAccelPin, GPIO_TypeDef *csGyroPort,
               uint16_t csGyroPin)
    : accel(spi, csAccelPort, csAccelPin), gyro(spi, csGyroPort, csGyroPin) {}

}  // namespace bmi088
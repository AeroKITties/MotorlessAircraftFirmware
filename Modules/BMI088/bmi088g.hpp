#pragma once

#include <stdint.h>

#include <Eigen/Dense>

#include "bmi088_defs.hpp"
#include "spi.h"

namespace bmi088 {
class BMI088_G {
   public:
    BMI088_G(SPI_HandleTypeDef *_spi, GPIO_TypeDef *_csPort, uint16_t _csPin);

    void setPowerMode(parameters::GYRO_PWR_MODE powerMode);
    void setRange(parameters::GYRO_RANGE range);
    void setBandwidth(parameters::GYRO_ODR_BANDWIDTH bandwidth);

    void updateAngularVelocity();
    Eigen::Vector3f getAngularVelocity() { return angularVelocity; }

   private:
    // SPI interface
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *csPort;
    uint16_t csPin;

    // SPI read/write
    void selectDevice();
    void unselectDevice();
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    void readRegisters(uint8_t reg, int byte_count, uint8_t *output_buffer);

    // private parameters
    parameters::GYRO_PWR_MODE currentPowerMode;
    parameters::GYRO_RANGE currentRange;
    parameters::GYRO_ODR_BANDWIDTH currentBandwidth;

    // Accel private variables
    uint8_t regReadBuffer[6];

    float accelToRawCoef;
    int16_t gyroRawValues[3];
    Eigen::Vector3f angularVelocity;

    // private methods
    void readRawAngularVelocityValues();
};
}  // namespace bmi088

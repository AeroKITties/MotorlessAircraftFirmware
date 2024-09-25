#pragma once

#include <stdint.h>

#include <Eigen/Dense>

#include "bmi088_defs.hpp"
#include "spi.h"

namespace bmi088 {
class BMI088_A {
   public:
    BMI088_A(SPI_HandleTypeDef *_spi, GPIO_TypeDef *_csPort, uint16_t _csPin);

    // Accel public methods
    uint8_t readChipID();

    void setRange(parameters::ACCEL_RANGE range);
    void setConfig(parameters::ACCEL_ODR outputDataRate, parameters::ACCEL_OSR oversamplingRate);
    void setPowerMode(parameters::ACCEL_PWR_MODE powerMode);
    void setPowerControl(parameters::ACCEL_PWR_CONTROL powerControl);

    void updateAcceleration();
    Eigen::Vector3f getAcceleration() { return acceleration; }

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

    // Accel private variables
    uint8_t regReadBuffer[6];

    float gravAccelToRawCoef;
    int16_t accelRawValues[3];
    Eigen::Vector3f acceleration;

    parameters::ACCEL_ODR currentODR;
    parameters::ACCEL_OSR currentOSR;
    parameters::ACCEL_RANGE currentRange;
    parameters::ACCEL_PWR_MODE currentPowerConfig;
    parameters::ACCEL_PWR_CONTROL currentPowerControl;

    // Accel private methods
    void readRawAccelValues();
};
}  // namespace bmi088

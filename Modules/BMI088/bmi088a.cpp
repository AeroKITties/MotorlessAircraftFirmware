#include "bmi088a.hpp"

#include <stdint.h>

#include "bmi088_defs.hpp"
#include "swo_debug.hpp"

namespace bmi088 {

BMI088_A::BMI088_A(SPI_HandleTypeDef *_spi, GPIO_TypeDef *_csPort, uint16_t _csPin) {
    spi = _spi;
    csPort = _csPort;
    csPin = _csPin;

    unselectDevice();
}

void BMI088_A::selectDevice() { HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET); }

void BMI088_A::unselectDevice() { HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET); }

void BMI088_A::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {static_cast<uint8_t>(registers::REG_WRITE | reg), value};

    selectDevice();
    HAL_SPI_Transmit(spi, buf, 2, HAL_MAX_DELAY);
    unselectDevice();
}

uint8_t BMI088_A::readRegister(uint8_t reg) {
    uint8_t command = registers::REG_READ | reg;
    uint8_t regValue;

    selectDevice();
    HAL_SPI_Transmit(spi, &command, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, &regValue, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, &regValue, 1, HAL_MAX_DELAY);
    unselectDevice();

    return regValue;
}

void BMI088_A::readRegisters(uint8_t reg, int byte_count, uint8_t *output_buffer) {
    uint8_t command = registers::REG_READ | reg;

    selectDevice();
    HAL_SPI_Transmit(spi, &command, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, output_buffer, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, output_buffer, byte_count, HAL_MAX_DELAY);
    unselectDevice();
}

uint8_t BMI088_A::readChipID() {
    uint8_t id = readRegister(registers::ACC_CHIP_ID);
    return id;
}

void BMI088_A::readRawAccelValues() {
    readRegisters(registers::ACC_X_LSB, 6, regReadBuffer);

    accelRawValues[0] = (int16_t)(regReadBuffer[1] * 256 + regReadBuffer[0]);
    accelRawValues[1] = (int16_t)(regReadBuffer[3] * 256 + regReadBuffer[2]);
    accelRawValues[2] = (int16_t)(regReadBuffer[5] * 256 + regReadBuffer[4]);
}

void BMI088_A::setRange(parameters::ACCEL_RANGE range) {
    currentRange = range;

    switch (range) {
        case parameters::ACCEL_RANGE_24G:
            gravAccelToRawCoef = 32768 / 24.0;
            break;

        case parameters::ACCEL_RANGE_12G:
            gravAccelToRawCoef = 32768 / 12.0;
            break;

        case parameters::ACCEL_RANGE_6G:
            gravAccelToRawCoef = 32768 / 6.0;
            break;

        case parameters::ACCEL_RANGE_3G:
            gravAccelToRawCoef = 32768 / 3.0;
            break;
    }

    writeRegister(registers::ACC_RANGE, range);
    HAL_Delay(200);
}

void BMI088_A::setConfig(parameters::ACCEL_ODR outputDataRate, parameters::ACCEL_OSR oversamplingRate) {
    currentODR = outputDataRate;
    currentOSR = oversamplingRate;

    uint8_t message = (1 << 7) | (oversamplingRate << 4) | outputDataRate;
    writeRegister(registers::ACC_CONF, message);
    HAL_Delay(200);
}

void BMI088_A::setPowerMode(parameters::ACCEL_PWR_MODE powerMode) {
    currentPowerConfig = powerMode;
    writeRegister(registers::ACC_PWR_CONF, powerMode);
    HAL_Delay(200);
}

void BMI088_A::setPowerControl(parameters::ACCEL_PWR_CONTROL powerControl) {
    currentPowerControl = powerControl;
    writeRegister(registers::ACC_PWR_CTRL, powerControl);
    HAL_Delay(200);
}

void BMI088_A::updateAcceleration() {
    readRawAccelValues();

    acceleration[0] = accelRawValues[0] / gravAccelToRawCoef;
    acceleration[1] = accelRawValues[1] / gravAccelToRawCoef;
    acceleration[2] = accelRawValues[2] / gravAccelToRawCoef;
}

}  // namespace bmi088
#include "bmi088g.hpp"

#include "bmi088_defs.hpp"

namespace bmi088 {

BMI088_G::BMI088_G(SPI_HandleTypeDef *_spi, GPIO_TypeDef *_csPort, uint16_t _csPin) {
    spi = _spi;
    csPort = _csPort;
    csPin = _csPin;

    unselectDevice();
}

void BMI088_G::selectDevice() { HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_RESET); }

void BMI088_G::unselectDevice() { HAL_GPIO_WritePin(csPort, csPin, GPIO_PIN_SET); }

void BMI088_G::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {static_cast<uint8_t>(registers::REG_WRITE | reg), value};

    selectDevice();
    HAL_SPI_Transmit(spi, buf, 2, HAL_MAX_DELAY);
    unselectDevice();
}

uint8_t BMI088_G::readRegister(uint8_t reg) {
    uint8_t command = registers::REG_READ | reg;
    uint8_t regValue;

    selectDevice();
    HAL_SPI_Transmit(spi, &command, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, &regValue, 1, HAL_MAX_DELAY);
    unselectDevice();

    return regValue;
}

void BMI088_G::readRegisters(uint8_t reg, int byte_count, uint8_t *output_buffer) {
    uint8_t command = registers::REG_READ | reg;

    selectDevice();
    HAL_SPI_Transmit(spi, &command, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi, output_buffer, byte_count, HAL_MAX_DELAY);
    unselectDevice();
}

void BMI088_G::setPowerMode(parameters::GYRO_PWR_MODE powerMode) {
    powerMode = powerMode;
    writeRegister(registers::GYRO_LPM1, powerMode);
    HAL_Delay(200);
}

void BMI088_G::setRange(parameters::GYRO_RANGE range) {
    currentRange = range;

    switch (range) {
        case parameters::GYRO_RANGE_2000:
            accelToRawCoef = 32768 / 34.90659;
            break;

        case parameters::GYRO_RANGE_1000:
            accelToRawCoef = 32768 / 17.4533;
            break;
        case parameters::GYRO_RANGE_500:
            accelToRawCoef = 32768 / 8.72665;
            break;

        case parameters::GYRO_RANGE_250:
            accelToRawCoef = 32768 / 4.36332;
            break;

        case parameters::GYRO_RANGE_125:
            accelToRawCoef = 32768 / 2.18166;
            break;
    }

    writeRegister(registers::GYRO_RANGE, range);
    HAL_Delay(200);
}

void BMI088_G::setBandwidth(parameters::GYRO_ODR_BANDWIDTH bandwidth) {
    currentBandwidth = bandwidth;
    writeRegister(registers::GYRO_BANDWIDTH, bandwidth);
    HAL_Delay(200);
}

void BMI088_G::readRawAngularVelocityValues() {
    readRegisters(registers::GYRO_RATE_X_LSB, 6, regReadBuffer);

    gyroRawValues[0] = (int16_t)(regReadBuffer[1] * 256 + regReadBuffer[0]);
    gyroRawValues[1] = (int16_t)(regReadBuffer[3] * 256 + regReadBuffer[2]);
    gyroRawValues[2] = (int16_t)(regReadBuffer[5] * 256 + regReadBuffer[4]);
}

void BMI088_G::updateAngularVelocity() {
    readRawAngularVelocityValues();

    angularVelocity[0] = gyroRawValues[0] / accelToRawCoef;
    angularVelocity[1] = gyroRawValues[1] / accelToRawCoef;
    angularVelocity[2] = gyroRawValues[2] / accelToRawCoef;
}

}  // namespace bmi088
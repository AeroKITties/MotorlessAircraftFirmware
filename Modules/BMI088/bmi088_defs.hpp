#pragma once

#include <stdint.h>

namespace bmi088 {

namespace parameters {

enum ACCEL_RANGE {
    ACCEL_RANGE_3G = 0x00,
    ACCEL_RANGE_6G = 0x01,
    ACCEL_RANGE_12G = 0x02,
    ACCEL_RANGE_24G = 0x03,
};

enum ACCEL_ODR {
    ACCEL_ODR_12p5 = 0x05,
    ACCEL_ODR_25 = 0x06,
    ACCEL_ODR_50 = 0x07,
    ACCEL_ODR_100 = 0x08,
    ACCEL_ODR_200 = 0x09,
    ACCEL_ODR_400 = 0x0A,
    ACCEL_ODR_800 = 0x0B,
    ACCEL_ODR_1600 = 0x0C,
};

enum ACCEL_OSR {
    ACCEL_OSR_4 = 0x00,
    ACCEL_OSR_2 = 0x01,
    ACCEL_OSR_NORMAL = 0x02,
};

enum ACCEL_PWR_MODE {
    ACCEL_PWR_ACTIVE_MODE = 0x00,
    ACCEL_PWR_SUSPEND_MODE = 0x03,
};

enum ACCEL_PWR_CONTROL {
    ACCEL_PWR_OFF = 0x00,
    ACCEL_PWR_ON = 0x04,
};

enum GYRO_PWR_MODE {
    GYRO_PWR_NORMAL = 0x00,
    GYRO_PWR_SUSPEND = 0x80,
    GYRO_PWR_DEEP_SUSPEND = 0x20,
};

enum GYRO_RANGE {
    GYRO_RANGE_2000 = 0x00,
    GYRO_RANGE_1000 = 0x01,
    GYRO_RANGE_500 = 0x02,
    GYRO_RANGE_250 = 0x03,
    GYRO_RANGE_125 = 0x04,
};

enum GYRO_ODR_BANDWIDTH {
    GYRO_ODR_2000_BAND_532 = 0x00,
    GYRO_ODR_2000_BAND_230 = 0x01,
    GYRO_ODR_1000_BAND_116 = 0x02,
    GYRO_ODR_400_BAND_47 = 0x03,
    GYRO_ODR_200_BAND_23 = 0x04,
    GYRO_ODR_100_BAND_12 = 0x05,
    GYRO_ODR_200_BAND_64 = 0x06,
    GYRO_ODR_100_BAND_32 = 0x07,
};

}  // namespace parameters

namespace registers {

const uint8_t REG_READ = 0x80;
const uint8_t REG_WRITE = 0x00;

const uint8_t ACC_CHIP_ID = 0x00;
const uint8_t ACC_ERR_REG = 0x02;
const uint8_t ACC_STATUS = 0x03;

const uint8_t ACC_X_LSB = 0x12;
const uint8_t ACC_X_MSB = 0x13;
const uint8_t ACC_Y_LSB = 0x14;
const uint8_t ACC_Y_MSB = 0x15;
const uint8_t ACC_Z_LSB = 0x16;
const uint8_t ACC_Z_MSB = 0x17;

const uint8_t ACC_CONF = 0x40;
const uint8_t ACC_RANGE = 0x41;

const uint8_t ACC_PWR_CONF = 0x7C;
const uint8_t ACC_PWR_CTRL = 0x7D;

const uint8_t GYRO_CHIP_ID = 0x00;
const uint8_t GYRO_RATE_X_LSB = 0x02;
const uint8_t GYRO_RATE_X_MSB = 0x03;
const uint8_t GYRO_RATE_Y_LSB = 0x04;
const uint8_t GYRO_RATE_Y_MSB = 0x05;
const uint8_t GYRO_RATE_Z_LSB = 0x06;
const uint8_t GYRO_RATE_Z_MSB = 0x07;

const uint8_t GYRO_LPM1 = 0x11;
const uint8_t GYRO_RANGE = 0x0F;
const uint8_t GYRO_BANDWIDTH = 0x10;
}  // namespace registers

}  // namespace bmi088

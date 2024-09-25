#pragma once

#include <stdint.h>

#include <Eigen/Dense>

#include "bmi088_defs.hpp"
#include "bmi088a.hpp"
#include "bmi088g.hpp"
#include "spi.h"

/* Пример использования:

/// Include-ы:
#include <Eigen/Dense>

#include "bmi088.h"



/// Инициализация:
bmi088::BMI088 imu = bmi088::BMI088(&hspi1, GPIOC, GPIO_PIN_4, GPIOA, GPIO_PIN_4);

/// Включение питания у датчиков:
imu.accel.setPowerMode(bmi088::parameters::ACCEL_PWR_ACTIVE_MODE);
imu.accel.setPowerControl(bmi088::parameters::ACCEL_PWR_ON);
imu.gyro.setPowerMode(bmi088::parameters::GYRO_PWR_NORMAL);

/// Установка пределов измерений, частоты обновления данных и занчения оверсемплинга:
imu.accel.setRange(bmi088::parameters::ACCEL_RANGE_24G);
imu.accel.setConfig(bmi088::parameters::ACCEL_ODR_200, bmi088::parameters::ACCEL_OSR_NORMAL);
imu.gyro.setRange(bmi088::parameters::GYRO_RANGE_1000);
imu.gyro.setBandwidth(bmi088::parameters::GYRO_ODR_1000_BAND_116);

/// Обновление данных в цикле:
imu.accel.updateAcceleration();
Eigen::Vector3f accel = imu.accel.getAcceleration();

imu.gyro.updateAngularVelocity();
Eigen::Vector3f gyro = imu.gyro.getAngularVelocity();

/// Вывод в консоль:
swoTerminal0 << accel.transpose() << std::endl;
swoTerminal1 << gyro.transpose() << std::endl;

*/

namespace bmi088 {
class BMI088 {
   public:
    BMI088(SPI_HandleTypeDef *spi, GPIO_TypeDef *csAccelPort, uint16_t csAccelPin, GPIO_TypeDef *csGyroPort,
           uint16_t csGyroPin);

    BMI088_A accel;
    BMI088_G gyro;

   private:
};
}  // namespace bmi088

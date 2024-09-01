#include "example_class.hpp"

#include "stm32f4xx_hal.h"

ExampleClass::ExampleClass() :  elevator_servo(0, 1200, 2200, ServoInputMode::BIDIRECTIONAL), 
                                ailerones_servo(1, 1000, 2000, ServoInputMode::BIDIRECTIONAL), 
                                f_pitch_stab(0)
{
    accel_x_history = std::vector<double> (2, 0);
    gyro_x_history = std::vector<double> (2, 0);
}

void ExampleClass::Configure() {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

    IMU_INIT(&hspi1);
    HAL_Delay(200);
    IMU_ENABLE_ALL();
    HAL_Delay(200);
    ACCEL_GOOD_SETTINGS();
    HAL_Delay(200);
    GYRO_GOOD_SETTINGS();

    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_Base_Start_IT(&htim6);

    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
}

/*!
 * @brief 20hz timer interrupt handler
 */
void ExampleClass::InterruptHandlerTim5() { PrintIMUData(); }

/*!
 * @brief 100hz timer interrupt handler
 */
void ExampleClass::InterruptHandlerTim6() {}

void ExampleClass::PrintIMUData() {
    Vector3 accel = ACCEL_READ_ACCELERATION();  // m/s^2
    Vector3 gyro = GYRO_READ_RATES();           // rad/s

    swoTerminal0 << std::fixed << std::setprecision(3);
    swoTerminal0 << "Ax: " << accel.x << "    Ay: " << accel.y << "    Az: " << accel.z;
    swoTerminal0 << "    Gx: " << gyro.x << "    Gy: " << gyro.y << "    Gz: " << gyro.z << std::endl;

    theta += pow(f, -1) * gyro.y;
    psi += pow(f, -1) * gyro.x;
    swoTerminal1 << "   theta = " << theta/3.1415*180 << std::endl;
    swoTerminal1 << "   psi = " << psi/3.1415*180 << std::endl;

    swoTerminal2 << "elevator_servo = " << theta/3.1415*5.5 << std::endl;
    swoTerminal2 << "ailerones_servo = " << psi/3.1415*7 << std::endl;

    swoTerminal3 << std::fixed << std::setprecision(3);
    ax = accel.x;
    ax_ = AccelFilter(accel_x_history, accel.x);
    swoTerminal3 << "Ax: " << ax << "    Ax_: " << ax_ << std::endl;
}
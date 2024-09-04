#include "example_class.hpp"

#include "stm32f4xx_hal.h"
#include "swo_debug.hpp"
#include <stdio.h>

ExampleClass::ExampleClass() :  elevator_servo(0, 1200, 2600, ServoInputMode::BIDIRECTIONAL), 
                                ailerones_servo(1, 1040, 2040, ServoInputMode::BIDIRECTIONAL), 
                                f_pitch_stab(0)
{
    accel_x_history = std::vector<double> (4, 0);
    gyro_x_history = std::vector<double> (4, 0);
    accel_y_history = std::vector<double> (4, 0);
    gyro_y_history = std::vector<double> (4, 0);
    accel_z_history = std::vector<double> (4, 0);
    gyro_z_history = std::vector<double> (4, 0);

    start_time = HAL_GetTick();
}

void ExampleClass::Configure() {
    Mount_SD("/");
    Create_File("LOG.txt");
    Unmount_SD("/");

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
void ExampleClass::InterruptHandlerTim5() { PrintIMUData(); Filter(); Angels(); PitchStab(); RollStab(); }

/*!
 * @brief 100hz timer interrupt handler
 */
void ExampleClass::InterruptHandlerTim6() {  }

void ExampleClass::PrintIMUData() {
    Vector3 accel = ACCEL_READ_ACCELERATION();  // m/s^2
    Vector3 gyro = GYRO_READ_RATES();           // rad/s

    Mount_SD("/");
    char buffer[80];
    std::sprintf(buffer, "Ax: %f, Ay: %f, Az: %f, Gx: %f, Gy: %f, Gz: %f \n", accel.x, accel.y, accel.z, gyro.x, gyro.y, gyro.z);
    Update_File("LOG.txt", buffer);
    Unmount_SD("/");


    swoTerminal0 << std::fixed << std::setprecision(3);
    swoTerminal0 << "Ax: " << accel.x << "    Ay: " << accel.y << "    Az: " << accel.z;
    swoTerminal0 << "    Gx: " << gyro.x << "    Gy: " << gyro.y << "    Gz: " << gyro.z << std::endl;
    swoTerminal0 << "time: " << HAL_GetTick() << std::endl;

    if (accel.x == accel.y && accel.x == accel.z && accel.x == 0){
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
    }

    if (HAL_GetTick() - start_time > 3000){
        if (HAL_GetTick() - start_time < 3500)
            HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        gamma += (pow(f, -1) * gyro.x);
        theta += (pow(f, -1) * gyro.y);

    if (! (accel.x == 0 && accel.y == 0 && accel.z == 0)){
    double theta_add = (3.14/2.0 - acos(-accel.x/9.87));
    if (!isnan(theta_add)){
        theta *= 0.6;
        theta += 0.4 * theta_add;
    }
    
    double gamma_add = (-(3.14/2.0 - acos(-accel.y/9.87)));
    if (!isnan(gamma_add)){
        gamma *= 0.6;
        gamma +=  0.4 * gamma_add;
        //gamma = gamma_add;
    }
    }
    }

    swoTerminal1 << "   theta = " << theta/3.1415*180 << std::endl;
    swoTerminal1 << "   gamma = " << gamma/3.1415*180 << std::endl;

    swoTerminal2 << "elevator_servo = " << theta/3.1415*5.5 << std::endl;
    swoTerminal2 << "ailerones_servo = " << gamma/3.1415*7 << std::endl;

    swoTerminal3 << std::fixed << std::setprecision(3);
    ax = accel.x;
    ax_ = AccelFilter(accel_x_history, accel.x);
    swoTerminal3 << "Ax: " << ax << "    Ax_: " << ax_ << std::endl;
}

void ExampleClass::Angels() {

}
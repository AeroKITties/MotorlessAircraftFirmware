#include "example_class.hpp"

#include "stm32f4xx_hal.h"
#include "swo_debug.hpp"


ExampleClass::ExampleClass() :  elevator_servo(0, 1200, 2600, ServoInputMode::BIDIRECTIONAL), 
                                ailerones_servo(1, 1040, 2040, ServoInputMode::BIDIRECTIONAL), 
                                f_pitch_stab(0)
{
    accel_x_history = std::vector<double> (20, 0);
    gyro_x_history = std::vector<double> (4, 0);
    accel_y_history = std::vector<double> (20, 0);
    gyro_y_history = std::vector<double> (4, 0);
    accel_z_history = std::vector<double> (20, 0);
    gyro_z_history = std::vector<double> (4, 0);
    start_time = HAL_GetTick();
}

void ExampleClass::Configure() {

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

    HAL_Delay(100);
    IMU_INIT(&hspi1);
    HAL_Delay(200);
    IMU_ENABLE_ALL();
    HAL_Delay(200);
    ACCEL_GOOD_SETTINGS();
    HAL_Delay(200);
    GYRO_GOOD_SETTINGS();
    HAL_Delay(200);

    HAL_TIM_Base_Start_IT(&htim5);
    HAL_Delay(5);
    HAL_TIM_Base_Start_IT(&htim6);

    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);

}

/*!
 * @brief 20hz timer interrupt handler
 */

void ExampleClass::InterruptHandlerTim5() { tim5_flag = true; }

/*!
 * @brief 100hz timer interrupt handler
 */
void ExampleClass::InterruptHandlerTim6() { tim6_flag = true; }

void ExampleClass::PrintIMUData() {
    Vector3 accel = ACCEL_READ_ACCELERATION();  // m/s^2
    Vector3 gyro = GYRO_READ_RATES();           // rad/s


    swoTerminal0 << std::fixed << std::setprecision(3);
    swoTerminal0 << "Ax: " << accel.x << "    Ay: " << accel.y << "    Az: " << accel.z;
    swoTerminal0 << "    Gx: " << gyro.x << "    Gy: " << gyro.y << "    Gz: " << gyro.z << std::endl;
    swoTerminal0 << "time: " << HAL_GetTick() << std::endl;
    logger.LogAccelRawData(accel.x, accel.y, accel.z, gyro.x, gyro.y, gyro.z);


    if (accel.x == accel.y && accel.x == accel.z && accel.x == 0){
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
    }

    double theta_add = 0;
    double gamma_add = 0;
    if (! (accel.x == 0 && accel.y == 0 && accel.z == 0)){
            theta_add = (3.14/2.0 - acos(-accel.x/9.87));
            gamma_add = (-(3.14/2.0 - acos(-accel.y/9.87)));
    }

    if (HAL_GetTick() - start_time > 3000){
        EnablePitchStab();
        EnableRollStab();
        if (HAL_GetTick() - start_time < 3500)
            HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        gamma += (pow(f, -1) * gyro.x);
        theta += (pow(f, -1) * gyro.y);
        if (!isnan(theta_add)){
            theta *= 0.8;
            theta += 0.2 * theta_add;
        }
        if (!isnan(gamma_add)){
            gamma *= 0.5;
            gamma +=  0.5 * gamma_add;
        }
    }
    else{
        theta = theta_add;
        gamma = gamma_add;
    }

    logger.LogAngles(theta, gamma);

    swoTerminal1 << "   theta = " << theta/3.1415*180 << std::endl;
    swoTerminal1 << "   gamma = " << gamma/3.1415*180 << std::endl;

    swoTerminal2 << "elevator_servo = " << theta/3.1415*5.5 << std::endl;
    swoTerminal2 << "ailerones_servo = " << gamma/3.1415*7 << std::endl;
}

void ExampleClass::Angles() {
}

void ExampleClass::Update() {
    if (tim5_flag) {
        tim5_flag = false;
    }

    if (tim6_flag) {
        tim6_flag = false; 
        Filter(); 
        PrintIMUData();
        Angles(); 
        PitchStab(); 
        RollStab();
        logger.LogServoOutput(elevator_servo.GetValue(), ailerones_servo.GetValue());
    }
}
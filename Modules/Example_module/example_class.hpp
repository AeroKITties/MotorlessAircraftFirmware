#pragma once

#include <iomanip>
#include <iostream>

#include "logger.hpp"
#include "main.h"
#include "servo.hpp"
#include "spi.h"
#include "swo_debug.hpp"
#include "tim.h"

extern "C" {
#include "IMU.h"
#include "sd_file_handling.h"
}

class ExampleClass {
   public:
    ExampleClass();

    void Update();
    void Configure();
    void InterruptHandlerTim5();  // 20hz
    void InterruptHandlerTim6();  // 100hz
    void EnablePitchStab();
    void DisablePitchStab();
    
    void EnableRollStab();
    void DisableRollStab();

    void EnableFilter();
    void DisableFilter();

   private:
    void PitchStab();
    void RollStab();
    void Filter();
    void Angles();
    //Настройки фильтра под 20Гц

    std::vector<double> accel_x_history;
    std::vector<double> gyro_x_history;
    std::vector<double> accel_y_history;
    std::vector<double> gyro_y_history;
    std::vector<double> accel_z_history;
    std::vector<double> gyro_z_history;
    Servo elevator_servo;
    Servo ailerones_servo;
    bool f_pitch_stab;
    bool f_roll_stab;
    bool f_filter;

    Vector3 accel;
    Vector3 gyro;
    double f = 20; //100 Hz (Tim6)

    float theta;
    float gamma;
    void PrintIMUData();
    float start_time; 

    float ax;
    float ax_;
    double AccelFilter(std::vector<double> & accel_history, double new_elem, bool make_discret = 0);
    bool tim5_flag = false;
    bool tim6_flag = false;
};
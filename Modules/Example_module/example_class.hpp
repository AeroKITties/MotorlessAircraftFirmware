#pragma once

#include <iomanip>
#include <iostream>

#include "main.h"
#include "servo.hpp"
#include "spi.h"
#include "swo_debug.hpp"
#include "tim.h"

extern "C" {
#include "IMU.h"
}

class ExampleClass {
   public:
    ExampleClass();
    void Configure();
    void InterruptHandlerTim5();  // 20hz
    void InterruptHandlerTim6();  // 100hz
    void EnablePitchStab();
    void DisablePitchStab();
    void PitchStab();

    void EnableRollStab();
    void DisableRollStab();
    void RollStab();

   private:
    std::vector<double> accel_x_history;
    std::vector<double> gyro_x_history;
    Servo elevator_servo;
    Servo ailerones_servo;
    bool f_pitch_stab;
    bool f_roll_stab;

    Vector3 accel;
    Vector3 gyro;
    double f = 100; //100 Hz (Tim6)

    float theta;
    float psi;
    void PrintIMUData();
    
    float ax;
    float ax_;
    double AccelFilter(std::vector<double> & accel_history, double new_elem);
};
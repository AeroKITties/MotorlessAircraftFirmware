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
}

class ExampleClass {
   public:
    ExampleClass();

    void Update();
    void Configure();
    void InterruptHandlerTim5();  // 20hz
    void InterruptHandlerTim6();  // 100hz

   private:
    Servo elevator_servo;
    void PrintIMUData();

    bool tim5_flag = false;
    bool tim6_flag = false;
};
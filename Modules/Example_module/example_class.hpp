#pragma once

#include <iostream>
#include <iomanip>

#include "servo.hpp"
#include "swo_debug.hpp"
#include "main.h"
#include "tim.h"
#include "spi.h"
extern "C"
{
#include "IMU.h"
}

class ExampleClass
{
public:
    ExampleClass();
    void Configure();
    void InterruptHandlerTim5(); // 20hz
    void InterruptHandlerTim6(); // 100hz

private:
    Servo elevator_servo;
    void PrintIMUData();
};
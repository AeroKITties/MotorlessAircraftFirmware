#pragma once

#include <iostream>
#include <iomanip>

#include "tim.h"
#include "spi.h"

#include "servo.hpp"
#include "swo-debug.hpp"
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
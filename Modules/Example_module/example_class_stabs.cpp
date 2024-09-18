#include "example_class.hpp"
#include "stm32f4xx_hal.h"


void ExampleClass::EnablePitchStab()
{
    f_pitch_stab = 1;
    elevator_servo.Enable();
}

void ExampleClass::DisablePitchStab()
{
    f_pitch_stab = 0;
    elevator_servo.Disable();
}

void ExampleClass::PitchStab()
{
    if (!f_pitch_stab){ return; }
    double k = 10;
    double servo_in = (theta - 0.156)/3.1415 * k;
    logger.LogPID('p', (theta - 0.1)/3.1415 * k, 0, -gyro.y*4);
    if (servo_in > 1) servo_in = 1;
    if (servo_in < -1) servo_in = -1;
    elevator_servo.SetValue(servo_in);
}

void ExampleClass::EnableRollStab()
{
    f_roll_stab = 1;
    ailerones_servo.Enable();
}

void ExampleClass::DisableRollStab()
{
    f_roll_stab = 0;
    ailerones_servo.Disable();
}

void ExampleClass::RollStab()
{
    if (!f_roll_stab){ return; }
    double k = 8.5;
    double servo_in = (gamma+0.04)/3.1415 * k;
    logger.LogPID('r', (gamma+0.05)/3.1415 * k, 0, -gyro.x*4);
    if (servo_in > 1) servo_in = 1;
    if (servo_in < -1) servo_in = -1;
    ailerones_servo.SetValue(servo_in);
}
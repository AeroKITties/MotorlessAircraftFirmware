#pragma once

#include <algorithm>

#include "servo_def.hpp"
#include "tim.h"


enum ServoInputMode {
    UNIDIRECTIONAL,  // Односторонний режим: значения от 0.0 до 1.0
    BIDIRECTIONAL    // Двусторонний режим: значения от -1.0 до 1.0
};

class Servo {
   public:
    Servo(int _servo_number, int _lower_limit, int _upper_limit, ServoInputMode _inputMode);
    void SetValue(float value);
    void SetRange(int _lower_limit, int _upper_limit);
    void Enable();
    void Disable();

   private:
    int servo_number;
    int lower_limit;
    int upper_limit;

    ServoInputMode inputMode;

    void SetServoTimerValueLL(int timer_value);
};
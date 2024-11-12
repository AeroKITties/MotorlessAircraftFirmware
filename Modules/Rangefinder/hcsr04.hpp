#pragma once
#include <stdint.h>

#include "usart.h"

class Hcsr04 {
   public:
    Hcsr04();
    void setRange(int new_range);
    int getRange();
    void updateRange();

   private:
    int range;
    uint8_t txBuffer[1] = {0xA0};
    uint8_t rxBuffer[3] = {0};
};

extern Hcsr04 rangefinder;
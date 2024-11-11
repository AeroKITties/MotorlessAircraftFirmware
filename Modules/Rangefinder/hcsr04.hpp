#include <stdint.h>

#include "usart.h"

class Hcsr04 {
   public:
    Hcsr04();
    void setRange(uint16_t new_range);
    uint16_t getRange();
    void updateRange();

   private:
    uint16_t range;
    uint8_t txBuffer[1] = {0x55};
};

extern Hcsr04 rangefinder;
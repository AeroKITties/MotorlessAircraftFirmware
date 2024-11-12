#include "hcsr04.hpp"

Hcsr04::Hcsr04() {}

void Hcsr04::setRange(int new_range) { range = new_range; }

int Hcsr04::getRange() { return range; }

void Hcsr04::updateRange() {
    range = 0;
    HAL_UART_Transmit(&huart1, txBuffer, 1, 100);
    HAL_UART_Receive(&huart1, rxBuffer, 3,1000);
     float distance = (((long)rxBuffer[0]<<16) | ((long)rxBuffer[1]<<8) | (long)rxBuffer[2]); // считаем дальность
    distance /= 1000;
    rangefinder.setRange((int)distance);
}

Hcsr04 rangefinder;
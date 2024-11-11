#include "hcsr04.hpp"

Hcsr04::Hcsr04() {}

void Hcsr04::setRange(uint16_t new_range) { range = new_range; }

uint16_t Hcsr04::getRange() { return range; }

void Hcsr04::updateRange() {
    range = 0;
    HAL_UART_Transmit(&huart1, txBuffer, 1, 100);
    while (range == 0) {
    }
}

Hcsr04 rangefinder{};
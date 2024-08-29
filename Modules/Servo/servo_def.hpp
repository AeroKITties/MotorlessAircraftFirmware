#pragma once

#include "tim.h"
#include <cstdint>
#include <vector>

struct ServoDef
{
    TIM_HandleTypeDef *htim;
    uint32_t channel;
};

/*!
 * @brief  Назначение таймеров и каналов для сервоприводов.
 */
const std::vector<ServoDef> servo_def = {
    {&htim12, TIM_CHANNEL_2},
    {&htim2, TIM_CHANNEL_1},
    {&htim12, TIM_CHANNEL_1},
    {&htim3, TIM_CHANNEL_2},
    {&htim3, TIM_CHANNEL_1},
    {&htim4, TIM_CHANNEL_3},
    {&htim4, TIM_CHANNEL_4},
    {&htim3, TIM_CHANNEL_4},
    {&htim3, TIM_CHANNEL_3},
    {&htim13, TIM_CHANNEL_1}};
#include "servo.hpp"

/*!
 * @brief
 * @param _servo_number Номер сервопривода (0-9)
 * @param _lower_limit Нижний предел значения сервопривода (например, 1000)
 * @param _upper_limit Верхний предел значения сервопривода (например, 2000)
 * @param _inputMode Вид входного сигнала: (Односторонний режим: от 0.0 до 1.0, Двусторонний режим: от -1.0 до 1.0)
 */
Servo::Servo(int _servo_number, int _lower_limit, int _upper_limit, ServoInputMode _inputMode)
{
    servo_number = _servo_number;
    inputMode = _inputMode;

    SetRange(_lower_limit, _upper_limit);
}

/*!
 * @brief Управление углом отклонения сервопривода
 * @param value Значение отклонения. (от 0.0 до 1.0 или от -1.0 до 1.0 в зависимости от установленного вида входного сигнала)
 */
void Servo::SetValue(float value)
{

    float value_us;
    if (inputMode == ServoInputMode::UNIDIRECTIONAL)
    {
        value = std::clamp(value, (float)0.0, (float)1.0);
        value_us = lower_limit + (upper_limit - lower_limit) * value;
    }
    else
    {
        value = std::clamp(value, (float)-1.0, (float)1.0);
        value_us = lower_limit + (upper_limit - lower_limit) * (value + 1.0) * 0.5;
    }

    int servo_timer_value = (int)(10000 * (value_us / 20000));
    SetServoTimerValueLL(servo_timer_value);
}

void Servo::SetServoTimerValueLL(int timer_value)
{
    switch (servo_def[servo_number].channel)
    {
    case TIM_CHANNEL_1:
        servo_def[servo_number].htim->Instance->CCR1 = timer_value;
        break;
    case TIM_CHANNEL_2:
        servo_def[servo_number].htim->Instance->CCR2 = timer_value;
        break;
    case TIM_CHANNEL_3:
        servo_def[servo_number].htim->Instance->CCR3 = timer_value;
        break;
    case TIM_CHANNEL_4:
        servo_def[servo_number].htim->Instance->CCR4 = timer_value;
        break;
    }
}

/*!
 * @brief Включение сервопривода
 */
void Servo::Enable()
{
    HAL_TIM_PWM_Start(servo_def[servo_number].htim, servo_def[servo_number].channel);
}

/*!
 * @brief Выключение сервопривода
 */
void Servo::Disable()
{
    HAL_TIM_PWM_Stop(servo_def[servo_number].htim, servo_def[servo_number].channel);
}

/*!
 * @brief  Изменение диапазона работы сервопривода
 * @param _lower_limit Нижний предел значения сервопривода (например, 1000)
 * @param _upper_limit Верхний предел значения сервопривода (например, 2000)
 */
void Servo::SetRange(int _lower_limit, int _upper_limit)
{
    lower_limit = _lower_limit;
    upper_limit = _upper_limit;
}
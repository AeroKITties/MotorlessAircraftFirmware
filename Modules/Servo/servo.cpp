#include "servo.hpp"

/*!
 * @brief Конструктор образа сервопривода
 * @param _servo_number Номер сервопривода (0-9)
 * @param _lower_limit Нижний предел значения сервопривода (например, 1000)
 * @param _upper_limit Верхний предел значения сервопривода (например, 2000)
 * @param _inputMode Вид входного сигнала: (Односторонний режим: от 0.0 до 1.0, Двусторонний режим: от -1.0 до 1.0)
 */
Servo::Servo(int _servo_number, int _lower_limit, int _upper_limit, ServoInputMode _inputMode)
{
    servo_number = _servo_number;
    lower_limit = _lower_limit;
    upper_limit = _upper_limit;
    inputMode = _inputMode;
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
        value_us = lower_limit + (upper_limit - lower_limit) * value;
    }
    else
    {
        value_us = lower_limit + (upper_limit - lower_limit) * (value + 1.0) * 0.5;
    }

    int servo_timer_value = (int)(10000 * (value_us / 20000));
    SetServoTimerValueLL(servo_timer_value);
}

void Servo::SetServoTimerValueLL(int timer_value)
{
    switch (servo_number)
    {
    case 0:
        htim13.Instance->CCR1 = timer_value;
        break;
    case 1:
        htim3.Instance->CCR3 = timer_value;
        break;
    case 2:
        htim3.Instance->CCR4 = timer_value;
        break;
    case 3:
        htim4.Instance->CCR4 = timer_value;
        break;
    case 4:
        htim4.Instance->CCR3 = timer_value;
        break;
    case 5:
        htim3.Instance->CCR1 = timer_value;
        break;
    case 6:
        htim3.Instance->CCR2 = timer_value;
        break;
    case 7:
        htim12.Instance->CCR1 = timer_value;
        break;
    case 8:
        htim2.Instance->CCR1 = timer_value;
        break;
    case 9:
        htim12.Instance->CCR2 = timer_value;
        break;
    }
}
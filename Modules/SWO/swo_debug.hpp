#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include "swo_backend.hpp"

// Класс для перенаправления вывода в функцию printString
class CustomStreamBuffer : public std::streambuf
{
public:
    explicit CustomStreamBuffer(int port) : port(port) {} // Конструктор принимает номер порта

protected:
    // Переопределяем функцию для обработки символов
    virtual int overflow(int c) override;

private:
    int port; // Номер порта, связанного с этим буфером
};

// Создаем несколько глобальных потоков для разных портов
extern std::ostream swoTerminal0;
extern std::ostream swoTerminal1;
extern std::ostream swoTerminal2;
extern std::ostream swoTerminal3;
extern std::ostream swoTerminal4;
extern std::ostream swoTerminal5;
extern std::ostream swoTerminal6;
extern std::ostream swoTerminal7;
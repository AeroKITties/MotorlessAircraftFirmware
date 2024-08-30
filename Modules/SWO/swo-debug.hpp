#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include "swo-backend.hpp"

// Класс для перенаправления вывода в функцию printString
class CustomStreamBuffer : public std::streambuf
{
protected:
    // Переопределяем функцию для обработки символов
    virtual int overflow(int c) override;
};

// Глобальный поток, использующий наш буфер
extern std::ostream swoTerminal;

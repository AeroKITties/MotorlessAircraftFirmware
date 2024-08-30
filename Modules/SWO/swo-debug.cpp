#include "swo-debug.hpp"

// Реализация кастомного буфера
int CustomStreamBuffer::overflow(int c)
{
    if (c != EOF)
    {
        std::string s(1, static_cast<char>(c)); // Преобразуем символ в строку
        printString(s);                         // Выводим символ с использованием printString
    }
    return c;
}

// Создаем экземпляр нашего кастомного буфера
CustomStreamBuffer customBuf;

// Создаем глобальный поток и привязываем его к нашему буферу
std::ostream swoTerminal(&customBuf);
#include "swo_debug.hpp"

// Реализация кастомного буфера
int CustomStreamBuffer::overflow(int c)
{
    if (c != EOF)
    {
        std::string s(1, static_cast<char>(c)); // Преобразуем символ в строку
        printString(port, s);                   // Выводим строку с использованием printString для указанного порта
    }
    return c;
}

// Создаем экземпляры кастомных буферов для разных портов
CustomStreamBuffer customBuf0(0);
CustomStreamBuffer customBuf1(1);
CustomStreamBuffer customBuf2(2);
CustomStreamBuffer customBuf3(3);
CustomStreamBuffer customBuf4(4);
CustomStreamBuffer customBuf5(5);
CustomStreamBuffer customBuf6(6);
CustomStreamBuffer customBuf7(7);
// Добавляйте столько буферов, сколько вам нужно

// Создаем глобальные потоки и привязываем их к нашим буферам
std::ostream swoTerminal0(&customBuf0);
std::ostream swoTerminal1(&customBuf1);
std::ostream swoTerminal2(&customBuf2);
std::ostream swoTerminal3(&customBuf3);
std::ostream swoTerminal4(&customBuf4);
std::ostream swoTerminal5(&customBuf5);
std::ostream swoTerminal6(&customBuf6);
std::ostream swoTerminal7(&customBuf7);
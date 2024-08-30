#include "swo-backend.hpp"

void printChar(char c)
{
    if ((ITM_TCR & 1) == 0)
    {
        return;
    }
    if ((ITM_ENA & 1) == 0)
    {
        return;
    }
    while ((ITM_STIM_U8 & 1) == 0)
        ;
    ITM_STIM_U8 = c;
}

void printCharArray(const char *s)
{
    while (*s)
    {
        printChar(*s++);
    }
}

void printString(std::string &s)
{
    printCharArray(s.c_str());
}
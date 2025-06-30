/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// isnormal: нормализованное ли число
int isnormal(double x) {
    uint64_t u = *(uint64_t*)&x;
    uint64_t exp = (u >> 52) & 0x7FF;
    return exp != 0 && exp != 0x7FF;
}

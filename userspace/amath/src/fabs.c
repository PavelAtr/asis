/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// fabs: модуль числа
double fabs(double x) {
    uint64_t u = *(uint64_t*)&x;
    u &= ~(1ULL << 63);
    return *(double*)&u;
}

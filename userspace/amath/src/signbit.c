/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// signbit: 1 если знак минус, иначе 0
int signbit(double x) {
    uint64_t u = *(uint64_t*)&x;
    return (u >> 63) & 1;
}

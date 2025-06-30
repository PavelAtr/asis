/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>
#include <math.h>

// isinf: бесконечность ли
int isinf(double x) {
    uint64_t u = *(uint64_t*)&x;
    uint64_t exp = (u >> 52) & 0x7FF;
    uint64_t frac = u & ((1ULL << 52) - 1);
    return (exp == 0x7FF && frac == 0) ? (signbit(x) ? -1 : 1) : 0;
}

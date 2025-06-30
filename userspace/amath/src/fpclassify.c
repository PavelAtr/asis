/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// fpclassify: классификация числа
enum {
    FP_NAN,
    FP_INFINITE,
    FP_ZERO,
    FP_SUBNORMAL,
    FP_NORMAL
};
int fpclassify(double x) {
    uint64_t u = *(uint64_t*)&x;
    uint64_t exp = (u >> 52) & 0x7FF;
    uint64_t frac = u & ((1ULL << 52) - 1);
    if (exp == 0x7FF) return frac ? FP_NAN : FP_INFINITE;
    if (exp == 0) return frac ? FP_SUBNORMAL : FP_ZERO;
    return FP_NORMAL;
}

/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// isfinite: конечное ли число
int isfinite(double x) {
    uint64_t u = *(uint64_t*)&x;
    uint64_t exp = (u >> 52) & 0x7FF;
    return exp != 0x7FF;
}

/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// rint: округление к ближайшему целому, как в FPU
double rint(double x) {
    double r;
    __asm__ ("frndint" : "=t"(r) : "0"(x));
    return r;
}

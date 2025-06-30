/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// atan2: арктангенс с учётом четверти
double atan2(double y, double x) {
    double r;
    __asm__ ("fpatan" : "=t"(r) : "0"(y), "u"(x));
    return r;
}

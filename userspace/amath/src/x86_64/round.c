/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// round: округление до ближайшего целого
double round(double x) {
    double r;
    __asm__ ("frndint" : "=t"(r) : "0"(x));
    double diff = x - r;
    if (diff > 0.5 || (diff == 0.5 && ((int64_t)r & 1))) r += 1.0;
    if (diff < -0.5 || (diff == -0.5 && ((int64_t)r & 1))) r -= 1.0;
    return r;
}

/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdint.h>

// modf: разбивает x на дробную и целую части
double modf(double x, double *iptr) {
    int64_t i = (int64_t)x;
    *iptr = (double)i;
    return x - *iptr;
}

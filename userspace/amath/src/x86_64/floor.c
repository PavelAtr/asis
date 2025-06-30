/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

double floor(double x) {
    double res;
    __asm__ __volatile__ (
        "frndint"
        : "=t"(res)
        : "0"(x)
    );
    // Если x < 0 и x не целое, уменьшаем на 1
    if (res > x) res -= 1.0;
    return res;
}

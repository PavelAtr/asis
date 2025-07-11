/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

double log2(double x) {
    double res;
    __asm__ __volatile__ (
        "fldln2\n\t"   // ST(0) = log_e(2)
        "fldl %1\n\t"  // ST(0) = x, ST(1) = log_e(2)
        "fyl2x\n\t"    // ST(0) = log2(x)
        "fstpl %0"
        : "=m"(res)
        : "m"(x)
        : "st"
    );
    return res;
}

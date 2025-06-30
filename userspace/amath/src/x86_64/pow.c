/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

double pow(double a, double b) {
    double res;
    __asm__ __volatile__ (
        "fldl %2\n\t"
        "fldl %1\n\t"
        "fyl2x\n\t"
        "fld %%st(0)\n\t"
        "frndint\n\t"
        "fsub %%st(1), %%st(0)\n\t"
        "fxch %%st(1)\n\t"
        "f2xm1\n\t"
        "fld1\n\t"
        "faddp\n\t"
        "fxch %%st(1)\n\t"
        "fscale\n\t"
        "fstp %%st(1)\n\t"
        : "=t"(res)
        : "m"(a), "m"(b)
    );
    return res;
}

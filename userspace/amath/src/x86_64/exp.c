/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

double exp(double x) {
    double res;
    __asm__ __volatile__ (
        "fldl   %1\n\t"     // ST(0) = x
        "fldl2e\n\t"        // ST(0) = log2(e), ST(1) = x
        "fmulp  %%st, %%st(1)\n\t" // ST(0) = x * log2(e)
        "fld     %%st(0)\n\t"      // дублируем x*log2(e)
        "frndint\n\t"              // округляем вниз (целая часть)
        "fsub    %%st, %%st(1)\n\t"// ST(0) = дробная часть, ST(1) = целая часть
        "fxch    %%st(1)\n\t"      // поменять местами
        "f2xm1\n\t"                // 2^(дробная часть) - 1
        "fld1\n\t"
        "faddp   %%st, %%st(1)\n\t"// 2^(дробная часть)
        "fscale\n\t"               // * 2^(целая часть)
        "fstp    %%st(1)\n\t"
        "fstpl   %0"
        : "=m"(res)
        : "m"(x)
        : "st"
    );
    return res;
}

/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

double log10(double x) {
    double res;
    __asm__ __volatile__ (
        "fldlg2\n\t"   // log10(2)
        "fxch\n\t"
        "fyl2x"
        : "=t"(res)
        : "0"(x)
    );
    return res;
}

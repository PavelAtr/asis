double sin(double x) {
    double res;
    __asm__ __volatile__ (
        "fsin"
        : "=t"(res)
        : "0"(x)
    );
    return res;
}

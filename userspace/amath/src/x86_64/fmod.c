double fmod(double a, double b) {
    double res;
    __asm__ __volatile__ (
        "1: fprem\n\t"
        "fstsw %%ax\n\t"
        "sahf\n\t"
        "jp 1b"
        : "=t"(res)
        : "0"(a), "u"(b)
        : "ax"
    );
    return res;
}

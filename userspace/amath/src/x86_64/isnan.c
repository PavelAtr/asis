int isnan(double x) {
    unsigned short status;
    __asm__ __volatile__ (
        "fxam\n\t"
        "fstsw %%ax\n\t"
        : "=a"(status)
        : "t"(x)
    );
    // Биты 10 и 8 = 1 => NaN
    return ((status & 0x4500) == 0x0100);
}

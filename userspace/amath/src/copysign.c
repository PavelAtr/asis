#include <stdint.h>

double copysign(double x, double y) {
    union { double d; uint64_t u; } ux = { x }, uy = { y };
    ux.u = (ux.u & ~(1ULL << 63)) | (uy.u & (1ULL << 63));
    return ux.d;
}

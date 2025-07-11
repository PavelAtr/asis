double fmin(double x, double y) {
    // Если хотя бы один аргумент NaN — возвращаем другой (POSIX/SUS поведение)
    if (x != x) return y;
    if (y != y) return x;
    return (x < y) ? x : y;
}

double fmax(double x, double y) {
    // Если хотя бы один аргумент NaN — возвращаем другой (POSIX/SUS поведение)
    if (x != x) return y;
    if (y != y) return x;
    return (x > y) ? x : y;
}

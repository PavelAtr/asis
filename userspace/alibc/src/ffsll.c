int ffsll(long long i) {
    if (i == 0) return 0;
    int pos = 1;
    while (!(i & 1)) {
        i >>= 1;
        pos++;
    }
    return pos;
}

int ffs(int i) {
    return ffsll((long long)i);
}

int ffsl(long i) {
    return ffsll((long long)i);
}

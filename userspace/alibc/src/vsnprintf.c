/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int itoa_simple(char *buf, size_t bufsz, unsigned long long val, int base, int is_signed, int upper) {
    char tmp[32];
    int pos = 0, len = 0;
    int neg = 0;
    if (is_signed && (long long)val < 0) {
        neg = 1;
        val = (unsigned long long)(-(long long)val);
    }
    do {
        int digit = val % base;
        tmp[pos++] = (digit < 10) ? ('0' + digit) : ((upper ? 'A' : 'a') + digit - 10);
        val /= base;
    } while (val && pos < (int)sizeof(tmp));
    if (neg) tmp[pos++] = '-';
    // reverse
    while (pos-- > 0 && len + 1 < (int)bufsz)
        buf[len++] = tmp[pos];
    if (len < (int)bufsz)
        buf[len] = 0;
    return len;
}

int vsnprintf(char *str, size_t size, const char *fmt, va_list ap) {
    size_t pos = 0, total = 0;
    const char *p = fmt;
    char numbuf[64];

    while (*p) {
        if (*p != '%') {
            if (str && pos + 1 < size)
                str[pos] = *p;
            pos ++;
            total++;
            p++;
            continue;
        }
        p++; // skip '%'
        int longflag = 0, longlongflag = 0, upper = 0;
        // Флаги длины
        while (*p == 'l') {
            if (longflag) longlongflag = 1;
            longflag = 1;
            p++;
        }
        if (*p == '%') {
            if (str && pos + 1 < size)
                str[pos] = '%';
            pos ++;
            total++;
            p++;
            continue;
        }
        switch (*p) {
            case 'd':
            case 'i': {
                long long v = longlongflag ? va_arg(ap, long long) :
                              longflag ? va_arg(ap, long) : va_arg(ap, int);
                itoa_simple(numbuf, sizeof(numbuf), v, 10, 1, 0);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                }
                break;
            }
            case 'u': {
                unsigned long long v = longlongflag ? va_arg(ap, unsigned long long) :
                                       longflag ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
                itoa_simple(numbuf, sizeof(numbuf), v, 10, 0, 0);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                }
                break;
            }
            case 'x':
            case 'X': {
                upper = (*p == 'X');
                unsigned long long v = longlongflag ? va_arg(ap, unsigned long long) :
                                       longflag ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
                itoa_simple(numbuf, sizeof(numbuf), v, 16, 0, upper);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                }
                break;
            }
            case 'o': {
                unsigned long long v = longlongflag ? va_arg(ap, unsigned long long) :
                                       longflag ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
                itoa_simple(numbuf, sizeof(numbuf), v, 8, 0, 0);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                }
                break;
            }
            case 'c': {
                int v = va_arg(ap, int);
                if (str && pos + 1 < size)
                    str[pos] = (char)v;
                pos ++;
                total++;
                break;
            }
            case 's': {
                const char *s = va_arg(ap, const char*);
                if (!s) s = "(null)";
                while (*s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                    s++;
                }
                break;
            }
            case 'p': {
                void *ptr = va_arg(ap, void*);
                unsigned long long v = (unsigned long long)(uintptr_t)ptr;
                if (str && pos + 1 < size)
                    str[pos++] = '0';
                if (str && pos + 1 < size)
                    str[pos++] = 'x';
                total += 2;
                itoa_simple(numbuf, sizeof(numbuf), v, 16, 0, 0);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos ++;
                    total++;
                }
                break;
            }
            case 'f': {
                double v = longflag ? va_arg(ap, double) : va_arg(ap, double);
                int ival = (int)v;
                double frac = v - ival;
                if (v < 0 && ival == 0) { // для -0.123
                    if (str && pos + 1 < size)
                        str[pos] = '-';
                    pos++;
                    total++;
                    v = -v;
                    ival = (int)v;
                    frac = v - ival;
                }
                // Целая часть
                itoa_simple(numbuf, sizeof(numbuf), ival, 10, 0, 0);
                for (char *s = numbuf; *s; ++s) {
                    if (str && pos + 1 < size)
                        str[pos] = *s;
                    pos++;
                    total++;
                }
                if (str && pos + 1 < size)
                    str[pos] = '.';
                pos++;
                total++;
                // Дробная часть (6 знаков)
                for (int i = 0; i < 6; ++i) {
                    frac *= 10;
                    int digit = (int)frac;
                    if (str && pos + 1 < size)
                        str[pos] = '0' + digit;
                        pos++;
                        total++;
                        frac -= digit;
                }
                break;
            }            
            default:
                // Неизвестный спецификатор — пропускаем
                break;
        }
        p++;
    }
    if (str && size)
        str[(pos < size) ? pos : size - 1] = 0;
    return total;
}

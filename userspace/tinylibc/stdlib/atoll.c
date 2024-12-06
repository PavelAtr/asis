#include <string.h>

char* digits = "0123456789abcdef";

long long degr(short base, unsigned int degree)
{
    long ret = 1;
    int i;
    for (i = 0; i < degree; i++)
	ret *= base;
    return ret;
}

short c2i(char digit)
{
    short i;
    for (i = 0; i < 16; i++)
	if (digits[i] == digit)
	    return i;
    return 0;
}

long long atoll(const char* str)
{
    short base = 10;
    char neg = 0;
    if (str[0] == '-')
    {
		str++;
		neg = 1;
    }
    if (str[0] == '0' && str[1] == 'x')
    {
		str++;
		str++;
		base = 16;
    }
    if (str[0] == '0')
    {
		str++;
		base = 8;
    }
    int len = strlen(str);
    int degree;
    int ind;
    long long ret = 0;
    for (ind = len - 1, degree = 0; ind >= 0; ind--, degree++)
        ret += c2i(str[ind]) * degr(base, degree);

    if (neg)
	    return -ret;

    return ret;
}

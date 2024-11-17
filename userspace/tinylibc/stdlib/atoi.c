#include <string.h>

char* digits = "0123456789abcdef";

long degr(short base, unsigned int degree)
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

long atoi(short base, const char* str)
{
    int len = strlen(str);
    int degree;
    int ind;
    long ret = 0;
    for (ind = len - 1, degree = 0; ind >= 0; ind--, degree++)
    {
	if (str[ind] == '-')
	    return -ret;
	ret += c2i(str[ind]) * degr(base, degree);
    }
    return ret;
}
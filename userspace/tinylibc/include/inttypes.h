#ifndef _INTTYPES_H
#define _INTTYPES_H

#include <sys/types.h>

intmax_t strtoimax(const char* nptr, char** endptr, int base);
uintmax_t strtoumax(const char* nptr, char** endptr, int base);

#endif
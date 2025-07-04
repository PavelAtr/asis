#ifndef _LIMITS_H
#define _LIMITS_H

#include <sys/types.h>
#include <time.h>

#define INT_MIN 0x80000000
#define INT_MAX 0x7FFFFFFF
#define LONG_MAX  0x7FFFFFFFFFFFFFFF
#define LONG_MIN 0x8000000000000000
#define CHAR_MIN 0x80
#define CHAR_MAX 0x7F
#define CHAR_BIT 8
#define SSIZE_MAX LONG_MAX

#define PATH_MAX 4096
#define NAME_MAX 255

#endif

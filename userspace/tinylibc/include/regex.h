#ifndef _REGEX_H
#define _REGEX_H

#include <sys/types.h>

typedef ssize_t  regoff_t;

typedef struct {
  size_t    re_nsub;  /* Number of parenthesized subexpressions */
} regex_t;

typedef struct {
  regoff_t  rm_so;    /* Byte offset from start of string
                      to start of substring */
  regoff_t  rm_eo;    /* Byte offset from start of string to
                      the first character after the end of
                      substring */
} regmatch_t;

#endif
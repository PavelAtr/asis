#ifndef _WCTYPE_H
#define _WCTYPE_H

#include <ctype.h>

typedef unsigned int wint_t;

wint_t towupper(wint_t wc);
wint_t towlower(wint_t wc);
#define iswspace(c) isspace(c)

#endif
#ifndef _WCHAR_H
#define _WCHAR_H

#include <sys/types.h>

#ifndef __WINT_TYPE__
# define __WINT_TYPE__ unsigned int
#endif

/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    __WINT_TYPE__ __wch;
    char __wchb[4];
  } __value;            /* Value so far.  */
} mbstate_t;

inline size_t wcrtomb(char *s, wchar_t wc, mbstate_t *ps)
{
  /* NOT REALIZED */
   return 0;
}

int wcwidth(wchar_t c);
wchar_t *wcschr(const wchar_t *wcs, wchar_t wc);
size_t wcslen(const wchar_t *s);

#endif
#ifndef _WCHAR_H
#define _WCHAR_H

#include <sys/types.h>
#include <stddef.h>

#ifndef __WINT_TYPE__
# define __WINT_TYPE__ unsigned int
#endif

typedef __WINT_TYPE__ wint_t;

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


int wcwidth(wchar_t c);
wchar_t *wcschr(const wchar_t *wcs, wchar_t wc);
size_t wcslen(const wchar_t *s);
size_t mbrtowc(wchar_t * pwc, const char s[], size_t n, mbstate_t * ps);
size_t wcrtomb(char * s, wchar_t wc, mbstate_t * ps);
size_t mbsrtowcs(wchar_t dest[], const char ** src,
                        size_t len, mbstate_t * ps);
size_t wcsrtombs(char dest[], const wchar_t ** src,
                        size_t len, mbstate_t * ps);
int mbsinit(const mbstate_t *ps);
wchar_t *wcscat(wchar_t *dest, const wchar_t *rc);
wchar_t *wmemcpy(wchar_t dest[], const wchar_t src[], size_t n);
int wcsncmp(const wchar_t s1[], const wchar_t s2[], size_t n);
wint_t btowc(int c);

#endif

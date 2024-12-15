#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

void* malloc(size_t size);
void free(void *ptr);

void printenv(void);
const char *getenv(const char *name);
#define secure_getenv(name) getenv(name)
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

long long atoll(const char *str);
#define atol(s) (long)atoll(s)
#define atoi(s) (int)atoll(s)

#define exit(s) _exit(s);
double strtod(const char* nptr, char** endptr);

#define EXIT_FAILURE    1       /* Failing exit status.  */
#define EXIT_SUCCESS    0       /* Successful exit status.  */
void *calloc(size_t nmemb, size_t size);

int mkostemps(char *template, int suffixlen, int flags);
#define mkstemp(template) mkostemps(template, 0, O_RDWR)
#define mkostemp(template, flags) mkostemps(template, 0, flags)
#define mkstemps(template, suffixlen) mkostemps(template, suffixlen, O_RDWR)

#endif

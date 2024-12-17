#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

void* malloc(size_t size);
void free(void *ptr);

void printenv(void);
char *getenv(const char *name);
#define secure_getenv(name) getenv(name)
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

long long atoll(const char *str);
#define atol(s) (long)atoll(s)
#define atoi(s) (int)atoll(s)

#define Exit(s) _exit(s);
#define exit(s) _exit(s);
double strtod(const char* nptr, char** endptr);

#define EXIT_FAILURE    1       /* Failing exit status.  */
#define EXIT_SUCCESS    0       /* Successful exit status.  */
void *calloc(size_t nmemb, size_t size);

int mkostemps(char *template, int suffixlen, int flags);
#define mkstemp(template) mkostemps(template, 0, O_RDWR)
#define mkostemp(template, flags) mkostemps(template, 0, flags)
#define mkstemps(template, suffixlen) mkostemps(template, suffixlen, O_RDWR)

void abort(void);

void *realloc(void *ptr, size_t size);
#define reallocf(ptr, size) realloc(ptr, size)
#define reallocarray(ptr, nmemb, size) realloc(ptr, nmemb*size)
const char * getprogname (void);

int cgetent (char **buf, char **db_array, const char *name);
int cgetset (const char *ent);
int cgetmatch (const char *buf, const char *name);
char * cgetcap (char *buf, const char *cap, int type);
int cgetnum (char *buf, const char *cap, long *num);
int cgetstr (char *buf, const char *cap, char **str);
int cgetustr (char *buf, const char *cap, char **str);
int cgetfirst (char **buf, char **db_array);
int cgetnext (char **buf, char **db_array);
int cgetclose (void);

long strtol(const char* nptr, char** endptr, int base);
long long strtoll(const char* nptr, char** endptr, int base);
#define strtonum(nptr, minval, maxval, errstr) atoll(nptr)

#define MB_CUR_MAX 2

#endif

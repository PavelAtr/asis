#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <alloca.h>
#include <locale.h>
#include <wchar.h>

void* malloc(size_t size);
void free(void *ptr);

void printenv(void);
char *getenv(const char *name);
char *secure_getenv(const char *name);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

extern __thread char** environ;
#define INIT_ENVIRON
extern __thread char** aargv;

long long atoll(const char *str);
long atol(const char *str);
int atoi(const char *str);

#define Exit(s) _exit(s)
#define _Exit(s) _exit(s)
#define exit(s) _exit(s)

double strtod(const char* nptr, char** endptr);

#define EXIT_FAILURE    1       /* Failing exit status.  */
#define EXIT_SUCCESS    0       /* Successful exit status.  */
void *calloc(size_t nmemb, size_t size);

int mkostemps(char *templ, int suffixlen, int flags);
int mkstemp(char *templ);
int mkostemp(char *templ, int flags);
int mkstemps(char *templ, int suffixlen);

void abort(void);

void *realloc(void *ptr, size_t size);
#define reallocf(ptr, size) realloc(ptr, size)
void *reallocarray(void *ptr, size_t nmemb, size_t size);
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
unsigned long strtoul(const char* nptr, char** endptr, int base);
unsigned long long strtoull(const char* nptr, char** endptr, int base);

#define strtonum(nptr, minval, maxval, errstr) atoll(nptr)

#define abs(j) (((j) < 0)? -(j) : (j))
#define labs(j) (((j) < 0)? -(j) : (j))
#define llabs(j) (((j) < 0)? -(j) : (j))

#define MB_CUR_MAX 2

long random(void);
#define rand() random()

void srandom(unsigned long seed);
char *initstate(unsigned long seed, char* state, long n);
char *setstate(char *state);

void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));
void *bsearch(const void *key, const void *base, size_t num, size_t width, int (*compare)(const void *, const void *));

int atexit(void (*function)(void));

long double strtold(const char* nptr, char** endptr);
#define strtod_l(s, p, l) strtold(s, p)

float strtof(const char* nptr, char** endptr);
#define strtof_l(s, p, l) strtof(s, p)

int mbtowc(wchar_t *pwc, const char s[], size_t n);
#define mbtowc_with_lock(pwc, s, n)  mbtowc(pwc, s, n) 
size_t mbstowcs(wchar_t dest[], const char* src, size_t n);
size_t wcstombs(char dest[], const wchar_t* src, size_t n);

int posix_memalign(void **memptr, size_t alignment, size_t size);
char *realpath(const char *path,
                      char *resolved_path);

#define srand(seed) srandom(seed)
#define rand() random()
char *mkdtemp(char *templ);
#define RAND_MAX        2147483647

#endif

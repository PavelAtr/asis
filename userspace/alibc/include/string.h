#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>
#include <sys/types.h>

size_t strlen(const char *s);
size_t strnlen(const char* s, size_t maxlen);
char* strstr(const char *haystack, const char *needle);
int strcmp(const char *s1, const char *s2);
char* strcpy(char* dst, const char* src);
char* strncpy(char* dst, const char* src, size_t sz);
char* stpncpy(char* dst, const char* src, size_t sz);
size_t strlcpy(char* dst, const char* src, size_t sz);
char* strdup(const char* s);
char* strndup(const char* s, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
void* mempcpy(void* dest, const void* src, size_t n);
char* strerror(int errnum);
char* strtok(char* str, const char* delim);
void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
char* strcat(char* dst, const char* src);
char* strrchr(const char *s, int c);
void* memmove(void* dest, const void* src, size_t n);
#define bcopy(src, dest, n) memmove(dest, src, n)
char* stpcpy(char* dst, const char* src);
char* strchr(const char *s, int c);
char *strchrnul(const char *s, int c);
int memcmp(const void* s1, const void* s2, size_t n);
int strncmp(const char* s1, const char* s2, size_t n);
void* memchr(const void* s, int c, size_t n);
void* memrchr(const void* s, int c, size_t n);
void *rawmemchr(const void* s, int c);
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
char *strpbrk(const char *s, const char *accept);
int strcoll(const char *s1, const char *s2);
char *strncat(char * dst, const char src[], size_t sz);
size_t strxfrm(char dest[], const char src[], size_t n);
#define index(s, c) strchr(s, c)
#define rindex(s, c) strrchr(s, c)

extern char* sys_siglist[35];
char *strsignal(int sig);

#define splitpath(path, dir, file) \
path = malloc(strlen(dir) + strlen(file) + 2); \
strcpy(path, dir); \
strcat(path, "/"); \
strcat(path, file); \
path[strlen(dir) + strlen(file) + 1] = '\0';

#endif

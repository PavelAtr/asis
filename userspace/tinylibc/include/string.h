#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

size_t strlen(const char *s);
char* strstr(const char *haystack, const char *needle);
int strcmp(const char *s1, const char *s2);
char* strcpy(char* dst, const char* src);
char *strncpy(char* dst, const char *restrict src, size_t sz);
#define strlcpy(dst, src, sz) strncpy(dst, src, sz)
char* strdup(const char *s);
void* memcpy(void* dest, const void* src, size_t n);
char* strerror(int errnum);
char* strtok(char* str, const char* delim);
void *memcpy(void* dest, const void* src, size_t n);
void *memset(void* s, int c, size_t n);
char *strcat(char* dst, const char* src);
char *strrchr(const char *s, int c);
#define memmove(dest, src, size) __builtin_memmove(dest, src, size)
char *stpcpy(char* dst, const char* src);
char *strchr(const char *s, int c);
int memcmp(const void* s1, const void* s2, size_t n);
int strncmp(const char* s1, const char* s2, size_t n);
#define strncasecmp(s1,s2, n) strncmp(s1, s2, n)
void bcopy(const void* src, void* dest, size_t n);

#endif

#ifndef _STRINGS_H
#define _STRINGS_H

void bzero(void* s, size_t n);
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char* s1, const char* s2, size_t n);

int ffs(int i);

#endif
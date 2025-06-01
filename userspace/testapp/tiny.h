#ifndef _TINY_H
#define _TINY_H

short itoa(long num, short base, char* buf);
int calcargv(char* cmdline, char** out);
char* unquote(char* str);

#endif

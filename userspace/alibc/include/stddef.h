#ifndef _STDDEF_H
#define _STDDEF_H

#ifdef UEFI
typedef unsigned short wchar_t;
#else
typedef int wchar_t;
#endif

#define NULL ((void*)0)
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif
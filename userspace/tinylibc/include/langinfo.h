#ifndef _LANGINFO_H
#define _LANGINFO_H

#include <locale.h>

typedef int nl_item;

char *nl_langinfo(nl_item item);
char *nl_langinfo_l(nl_item item, locale_t locale);

#define CODESET 1

#endif
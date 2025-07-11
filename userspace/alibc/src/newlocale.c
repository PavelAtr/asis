#include <locale.h>

/* NOT REALIZED */

locale_t newlocale(int category_mask, const char *locale,
                          locale_t base)
{
   return base;
}

void freelocale(locale_t locobj)
{
}

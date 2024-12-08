#include <tinysys.h>
#include <stddef.h>
#include <string.h>

device devices[MAXDEV];

device* sys_get_device_byname(const char* path, mode_t devtype)
{
   short i;
   for (i = 0; i < MAXDEV; i++)
      if (devices[i].file) {
         if (strcmp(devices[i].file, path) == 0 && devices[i].type & devtype) {
            return &devices[i];
         }
      }
   return NULL;
}

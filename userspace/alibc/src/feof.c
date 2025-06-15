#include <stdio.h>

int feof(FILE *stream)
{
INIT_afds
   if (!stream) {
      return 1; // EOF for null stream
   }
   if (stream->type == F_PIPE) {
      if (((apipe*)stream)->pbuf->refcount <= 1)
         return 1;
   }
   if (stream->type == F_FILE) {
      if (((FILE*)stream)->flags & FILE_INFINITY) {
         return 0;
      }
   }
   if (stream->pos >= stream->size - 1) {
      return 1;
   }
   return 0;
}

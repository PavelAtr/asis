#include <sys/types.h>

mode_t global_mask = 0;

mode_t umask(mode_t mask)
{
   global_mask = mask;
   return global_mask;
}
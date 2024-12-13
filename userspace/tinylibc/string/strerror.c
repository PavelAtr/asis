#include <string.h>
#include <errno.h>

char* errors[20] = {
   "Successfully",
   "Insufficient privileges",
   "Access denied",
   "No such object",
   "Not enought mem",
   "Alredy exist",
   "Not a directory",
   "Not supported",
   "Is a directory",
   "Invalid seek",
   "Result too large",
   "Bad file descriptor",
   "Not enought space",
   "Invalid value",
   "Function not implemented",
};

char* strerror(int errnum)
{
   return errors[errnum];
}

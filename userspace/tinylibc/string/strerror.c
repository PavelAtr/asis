#include <string.h>
#include <errno.h>

char* errors[30] = {
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
   "Inappropriate file type or format",
   "File name too long",
   "File too large",
   "Broken pipe",
   "Interrupted function call",
   "Resource temporarily unavailable",
};

char* strerror(int errnum)
{
   return errors[errnum];
}

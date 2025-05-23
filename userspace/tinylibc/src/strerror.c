#include <string.h>
#include <errno.h>

int* errnoptr;

char* errors[40] = {
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
"Too many levels of symbolic links",
"No such process",
"Argument list too long",
"Too many open files",
"Exec format error",
"Operation would block",
"Bad file descriptor",
"Invalid request descriptor",
"Operation not supported on socket",
"Device or resource busy",
"Address family not supported",
"Input/output error",
"Value too large to be stored in data type ",
"Invalid cross-device link",
"Invalid or incomplete multibyte or wide character",
"Connection timed out",
"Stale file handle",
};

char* strerror(int errnum)
{
   return errors[errnum];
}

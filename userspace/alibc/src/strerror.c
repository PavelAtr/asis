#include <string.h>
#include <errno.h>

int* errnoptr;

char* errors[60] = {
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
"The named attribute does not exist, or the process has no access to this attribute",
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
"Text file busy",
"Too many links",
"Disk quota exceeded",
"Read-only filesystem",
"Directory not empty",
"No child processes",
"Too many open files in system",
"Inappropriate I/O control operation ",
"Resource deadlock avoided ",
"Operation in progress",
"Connection reset",
"Cannot send after transport endpoint shutdown",
"Bad address",
"Protocol error",
"Connection refused",
"The socket is not connected",
"No such device",
"No such device or address",
"Not a socket",
"Bad message"
};

char* strerror(int errnum)
{
   return errors[errnum];
}

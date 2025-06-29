#include <unistd.h>
#include <string.h>

size_t confstr(int name, char* buf, size_t size)
{
    char* retstr;
    switch (name)
    {
	case _CS_GNU_LIBC_VERSION:
	    retstr = "none";
	    break;
	case _CS_GNU_LIBPTHREAD_VERSION:
	    retstr = "none";
	    break;
	case _CS_PATH:
	    retstr = PATH;
    }
    size_t ret = (size < strlen(retstr)) ? size : strlen(retstr);
    strncpy(buf, retstr, ret);
    return ret;
}


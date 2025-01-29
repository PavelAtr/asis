#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>
#include <errno.h>

int fileno(FILE *stream)
{
   return stream->fd;
}

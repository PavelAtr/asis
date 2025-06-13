#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>
#include <errno.h>

int fileno(FILE *stream)
{
INIT_afds
   return stream->fd;
}

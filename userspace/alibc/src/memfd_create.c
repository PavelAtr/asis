#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

int memfd_create(const char *name, unsigned int flags)
{

   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   afds[fd] = malloc(sizeof(amemfile));
   afds[fd]->type = F_NAMEDMEM;
   initfile(afds[fd]);
   afds[fd]->file = strdup(name);
   afds[fd]->size = -1;
   if (flags & MFD_CLOEXEC) {
      afds[fd]->fdflags |= O_CLOEXEC;
   }
   ((amemfile*)afds[fd])->membuf = asyscall(SYS_SHARED, "memfd", afds[fd]->file, "", &afds[fd]->size, 0, 0);
   return fd;
}

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int memfd_create(const char *name, unsigned int flags)
{

   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   FILE* ret =afds[fd];
   ret = malloc(sizeof(amemfile));
   initfile(ret);
   char* cwd = get_current_dir_name();
   ret->file = fullpath(cwd, name);
   ret->size = 0;
   if (flags & MFD_CLOEXEC) {
      ret->fdflags |= O_CLOEXEC;
   }
   ret->type = F_NAMEDMEM;
   ((amemfile*)ret)->membuf = asyscall(SYS_SHARED, "memfd", ret->file, "", &ret->size, 0, 0);
   return fd;
}

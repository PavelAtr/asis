#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/eventfd.h>

int eventfd(unsigned int initval, int flags)
{
   INIT_afds
   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   afds[fd] = (FILE*)calloc(1, sizeof(aeventfd));
   if (!afds[fd]) {
      errno = ENOMEM;
      return -1;
   }
   aeventfd* efd = (aeventfd*)afds[fd];
   efd->type = F_EVENTFD;
   efd->fd = fd;
   efd->value = (unsigned long*)malloc(sizeof(unsigned long));
   if (!efd->value) {
      free(efd);
      errno = ENOMEM;
      return -1;
   }
   *efd->value = initval;
   if (flags & EFD_CLOEXEC) {
      efd->fdflags |= O_CLOEXEC;
   }
   efd->flags = flags; // Initialize flags
   efd->fd_refcount = 1; // Set initial reference count
   
   return fd;
}

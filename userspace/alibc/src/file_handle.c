#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int name_to_handle_at(int dirfd, const char *pathname,
                 struct file_handle *handle,
                 int *mount_id, int flags)
{
   INIT_afds
   if (!fd_is_valid(dirfd)) {
      errno = EBADFD;
      return -1;
   }
   strcpy(handle->f_handle, afds[dirfd]->file);
   strcpy(handle->f_handle + strlen(afds[dirfd]->file), "/");
   strcpy(handle->f_handle + strlen(afds[dirfd]->file) + 1, pathname);
   handle->handle_bytes = strlen(handle->f_handle) + sizeof(struct file_handle);
   *mount_id = 0; /* fake */
   return 0;
}

int open_by_handle_at(int mount_fd, struct file_handle *handle,
                 int flags) {
    return open(handle->f_handle, flags);
}


#include <sys/xattr.h>

/* NOT REALIZED */

ssize_t getxattr(const char *path, const char *name,
                void* value, size_t size)
{
   return 8;
}

ssize_t lgetxattr(const char *path, const char *name,
                void* value, size_t size)
{
   return 8;
}

ssize_t fgetxattr(int fd, const char *name,
                void* value, size_t size)
{
   return 8;
}

ssize_t listxattr(const char *path, char *list, size_t size)
{
   return 0;
}

ssize_t llistxattr(const char *path, char *list, size_t size)
{
   return 0;
}

ssize_t flistxattr(int fd, char *list, size_t size)
{
   return 0;
}

 int setxattr(const char *path, const char *name,
             const void* value, size_t size, int flags)
{
   return 0;
}

int lsetxattr(const char *path, const char *name,
             const void* value, size_t size, int flags)
{
   return 0;
}

int fsetxattr(int fd, const char *name,
             const void* value, size_t size, int flags)
{
   return 0;
}

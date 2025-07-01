#include <sys/inotify.h>
#include <fcntl.h>

/* NOT REALIZED */

int inotify_init(void)
{
    return open("inotify.stub", O_CREAT|O_RDONLY);
}

int inotify_init1(int flags)
{
   return inotify_init();
}

int inotify_add_watch(int fd, const char *pathname, uint32_t mask)
{
   return 0;
}

int inotify_rm_watch(int fd, int wd)
{
   return 0;
}


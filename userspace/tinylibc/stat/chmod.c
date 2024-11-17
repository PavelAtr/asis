#include <syscall.h>
#include <sys/stat.h>
#include <stddef.h>

int chmod(const char *pathname, mode_t mode)
{
    struct stat st;
    stat(pathname, &st);
    return syscall(SYS_MODNOD, pathname, NULL, st.st_uid, st.st_gid, mode);
}
#include <sys/types.h>
#include <sys/mman.h>

int shm_open(const char *name, int oflag, mode_t mode)
{
    return memfd_create(name, 0);
}

int shm_unlink(const char *name)
{
    return 0;
}
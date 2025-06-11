#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#include <sys/types.h>

#define PROT_READ       0x1             /* page can be read */
#define PROT_WRITE      0x2             /* page can be written */
#define PROT_EXEC       0x4             /* page can be executed */

#define MAP_SHARED      0x01            /* Share changes */
#define MAP_PRIVATE     0x02            /* Changes are private */
#define MAP_SHARED_VALIDATE 0x03        /* share + validate extension flags */
#define MAP_TYPE        0x0f            /* Mask for type of mapping */
#define MAP_FIXED       0x10            /* Interpret addr exactly */
#define MAP_ANONYMOUS   0x20            /* don't use a file */

#define MAP_FAILED      ((void *) -1)

void* mmap(void* addr, size_t length, int prot, int flags,
   int fd, off_t offset);
int munmap(void* addr, size_t length);

int memfd_create(const char *name, unsigned int flags);
#define MFD_CLOEXEC 0x1
#define MFD_ALLOW_SEALING 0x2
#define MFD_HUGETLB 0x4

#endif
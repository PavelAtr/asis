#include <asis.h>
#include <sys/resource.h>

int sys_getrlimit(int resource, void* r)
{
	struct rlimit* rlim = r;
	switch (resource) {
		case RLIMIT_NPROC:
		   rlim->rlim_cur = MAXPROC;
           rlim->rlim_max = MAXPROC;
		   break;
		default:  
		   break;
	}
    return 0;
}

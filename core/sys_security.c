#include <tinysys.h>
#include <sys/capability.h>
#include <errno.h>

bool_t capable(int_t cap)
{
   if (current->uid == 0) {
      return 1;
   }
   return 0;
}

bool_t in_group(gid_t gid)
{
   if (gid == current->uid) {
      return 1;
   }
   return 0;
}

secmodel default_security = {
   &capable,
   &in_group,
};

secmodel* security = &default_security;

int_t sys_setuid(uid_t uid)
{
   if (security->capable(CAP_SETUID)) {
      current->uid = uid;
      return 0;
   }
   *current->sys_errno = EPERM;
   return -1;
}

int_t sys_setgid(gid_t gid)
{
   if (security->in_group(gid) || security->capable(CAP_SETUID)) {
      current->gid = gid;
      return 0;
   }
   *current->sys_errno = EPERM;
   return -1;
}

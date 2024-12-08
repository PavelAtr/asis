#include <tinysys.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

proc sys;
char* argv[1] = {"system"};

void init_proc()
{
  sys.argv = argv;
  cpu[0] = &sys;
  current = cpu[0];
}

char** copyenv(char*const* e)
{
  char** copy = sys_malloc(sizeof(char*) * COREMAXENV);
  memset(copy, 0x0, sizeof(char*) * COREMAXENV);
  int_t i;
  for (i = 0; i < COREMAXENV - 2; i++) {
    if (e) {
      if ((e[i])[0] == '\0')
        copy[i] = e[i];
      else
        copy[i] = strdup(e[i]);
    } else {
      copy[i] = "";
    }
  }
  copy[COREMAXENV - 1] = NULL;
  return copy;
}
void freeenv(char*const* e)
{
  int_t i;
  for (i = 0; i < COREMAXENV - 2; i++)
    if ((e[i])[0] != '\0')
      sys_free(e[i]);
  sys_free((void*)e);
}

void* copy_fds(void* infds)
{
  fdesc* fds = infds;
  fdesc* ret = sys_malloc(sizeof(fdesc) * COREMAXFD);
  memset(ret, 0x0, sizeof(fdesc) * COREMAXFD);
  int_t i;
  if (infds)
    for (i = 0; i < COREMAXFD; i++) {
      if (!(fds[i].flags & O_CLOEXEC)) {
        if (fds[i].stream) {
          ret[i].stream = sys_malloc(sizeof(FILE));
          memset(ret[i].stream, 0x0, sizeof(FILE));
          if (fds[i].stream->file)
            ret[i].stream->file = strdup(fds[i].stream->file);
          ret[i].stream->pos = fds[i].stream->pos;
          ret[i].stream->size = fds[i].stream->size;
          ret[i].flags = fds[i].flags;
        }
        ret[i].rpipe = fds[i].rpipe;
        ret[i].wpipe = fds[i].wpipe;
        if (fds[i].rpipe)
          fds[i].rpipe->nlink++;
        if (fds[i].wpipe)
          fds[i].wpipe->nlink++;
      }
    }
  return ret;
}

void free_fds(proc* task)
{
  fdesc* fds = task->fds;
  int_t i;
  for (i = 0; i < COREMAXFD; i++) {
    if (fds[i].stream) {
      if (fds[i].stream->file)
        sys_free(fds[i].stream->file);
      sys_free(fds[i].stream);
    }
    if (fds[i].rpipe) {
      fds[i].rpipe->nlink--;
      if (fds[i].rpipe->nlink == 0)
        sys_free(fds[i].rpipe);
    }
    if (fds[i].wpipe) {
      fds[i].wpipe->nlink--;
      if (fds[i].wpipe->nlink == 0)
        sys_free(fds[i].wpipe);
    }
  }
  sys_free(fds);
}

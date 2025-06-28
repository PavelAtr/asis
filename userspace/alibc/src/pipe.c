#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pipe2(int pipefd[2], int flags)
{
   INIT_afds
   int fd0 = get_free_fd();
   afds[fd0] = calloc(1, sizeof(apipe));
   ((apipe*)afds[fd0])->type = F_PIPE;
   initfile(afds[fd0]);
   ((apipe*)afds[fd0])->fd = fd0;
   ((apipe*)afds[fd0])->flags |= FILE_INFINITY;

   int fd1 = get_free_fd();
   afds[fd1] = calloc(1, sizeof(apipe));
   ((apipe*)afds[fd1])->type = F_PIPE;
   initfile(afds[fd1]);
   ((apipe*)afds[fd1])->fd = fd1;
   ((apipe*)afds[fd1])->flags |= FILE_INFINITY;
   afds[fd0]->file = strdup("pipe");
   afds[fd1]->file = strdup("pipe");
   if (fd0 == -1 || fd1 == -1)
   {
      freefile(afds[fd0]);
      freefile(afds[fd1]);
      errno = ENOMEM;
      return -1;
   }

   ((apipe*)afds[fd0])->pbuf = calloc(1, sizeof(pipebuf));
   ((apipe*)afds[fd1])->pbuf = ((apipe*)afds[fd0])->pbuf;
   ((apipe*)afds[fd0])->pbuf->refcount = 2;

   pipefd[0] = fd0;
   pipefd[1] = fd1;

   return 0;
}

int pipe(int pipefd[2])
{
   return pipe2(pipefd, 0);
}

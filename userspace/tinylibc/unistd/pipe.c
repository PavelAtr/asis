#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pipe2(int pipefd[2], int flags)
{
   int fd0 = pipefd[0];
   int fd1 = pipefd[1];

   fd0 = get_free_fd();
   fds[fd0] = calloc(1, sizeof(FILE));
   fds[fd0]->file = strdup("pipe");
   fds[fd0]->fd = fd0;

   fd1 = get_free_fd();
   fds[fd1] = calloc(1, sizeof(FILE));
   fds[fd1]->file = strdup("pipe");
   fds[fd1]->fd = fd1;

   if (fd0 == -1 || fd1 == -1)
   {
      freefile(fds[fd0]);
      freefile(fds[fd1]);
      errno = ENOMEM;
      return -1;
   }

   fds[fd0]->wpipe = calloc(1, sizeof(pipebuf));
   fds[fd1]->wpipe = calloc(1, sizeof(pipebuf));

   if (!fds[fd0]->wpipe || !fds[fd1]->wpipe)
   {
      freefile(fds[fd0]);
      freefile(fds[fd1]);
      errno = ENOMEM;
      return -1;
   }

   fds[fd0]->rpipe = fds[fd1]->wpipe;
   fds[fd1]->rpipe = fds[fd0]->wpipe;
   fds[fd0]->rpipe->nlink = 2;
   fds[fd0]->wpipe->nlink = 2;

   pipefd[0] = fd0;
   pipefd[1] = fd1;

   return 0;
}

int pipe(int pipefd[2])
{
   return pipe2(pipefd, 0);
}

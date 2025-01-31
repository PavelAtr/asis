#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pipe2(int pipefd[2], int flags)
{
   int fd0 = get_free_fd();
   (*fds)[fd0] = calloc(1, sizeof(FILE));
   (*fds)[fd0]->file = strdup("pipe");
   (*fds)[fd0]->fd = fd0;
   (*fds)[fd0]->flags |= FILE_INFINITY;

   int fd1 = get_free_fd();
   (*fds)[fd1] = calloc(1, sizeof(FILE));
   (*fds)[fd1]->file = strdup("pipe");
   (*fds)[fd1]->fd = fd1;
   (*fds)[fd1]->flags |= FILE_INFINITY;

   if (fd0 == -1 || fd1 == -1)
   {
      freefile((*fds)[fd0]);
      freefile((*fds)[fd1]);
      errno = ENOMEM;
      return -1;
   }

   (*fds)[fd0]->pipbuf = calloc(1, sizeof(pipebuf));

   (*fds)[fd1]->pipbuf = (*fds)[fd0]->pipbuf;
   (*fds)[fd0]->pipbuf->nlink = 2;

   pipefd[0] = fd0;
   pipefd[1] = fd1;

   return 0;
}

int pipe(int pipefd[2])
{
   return pipe2(pipefd, 0);
}

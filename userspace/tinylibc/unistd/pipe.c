#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pipe2(int pipefd[2], int flags)
{
   pipefd[0] = get_free_fd();
   pipefd[1] = get_free_fd();
   if (pipefd[0] == -1 || pipefd[1] == -1)
   {
      errno = ENOMEM;
      return -1;
   }
   fds[pipefd[0]]->stream = malloc(sizeof(FILE));
   fds[pipefd[1]]->stream = malloc(sizeof(FILE));
   fds[pipefd[0]]->stream->file = strdup("pipe");
   fds[pipefd[1]]->stream->file = strdup("pipe");

   fds[pipefd[0]]->wpipe = malloc(sizeof(pipebuf));
   memset(fds[pipefd[0]]->wpipe, 0x0, sizeof(pipebuf));
   fds[pipefd[1]]->wpipe = malloc(sizeof(pipebuf));
   memset(fds[pipefd[1]]->wpipe, 0x0, sizeof(pipebuf));

   fds[pipefd[0]]->rpipe = fds[pipefd[1]]->wpipe;
   fds[pipefd[1]]->rpipe = fds[pipefd[0]]->wpipe;
   fds[pipefd[0]]->rpipe->nlink = 2;
   fds[pipefd[0]]->wpipe->nlink = 2;

   return 0;
}

int pipe(int pipefd[2])
{
   return pipe2(pipefd, 0);
}

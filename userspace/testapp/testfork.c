#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <tiny.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  pid_t child1 = fork();
  if (child1 == 0) {
    int i;
    for (i = 0; i < 10; i++) {
      puts("Child1\n");
      usleep(100);
    }
    return 0;
  } else {
    pid_t child2 = fork();
    if (child2 == 0) {
      int i;
      for (i = 0; i < 10; i++) {
        puts("Child2\n");
        usleep(100);
      }
      return 0;
    }
  }
  int ret;
  while (wait(&ret) != -1);
  return 0;
}

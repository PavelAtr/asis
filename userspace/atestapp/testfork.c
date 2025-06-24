#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syscall.h>

char* origin = "testfork"; /* GARBAGE */

__thread int a = 5;

int main(int argc, char** argv)
{
   pid_t child1 = fork();
   if (child1 == 0) {
      int i;
      for (i = 0; i < 10; i++) {
         printf("Child1 %d\n", a);
         a = 1;
         usleep(1);
      }
      return 5;
   } else {
      pid_t child2 = fork();
      if (child2 == 0) {
         int i;
         for (i = 0; i < 10; i++) {
            printf("Child2 %d\n", a);
            a = 2;
            usleep(1);
         }
         return 10;
      }
   }
   int ret;
   while (wait(&ret) != -1) printf("ret=%d\n", ret);
   return 0;
}

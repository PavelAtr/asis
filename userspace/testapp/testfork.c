#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

__thread int a;

int main(int argc, char** argv)
{
   pid_t child1 = fork();
   if (child1 == 0) {
      int i;
      a = 1;
      for (i = 0; i < 10; i++) {
         printf("Child1 %d\n", a);
         usleep(1);
      }
      return 0;
   } else {
      pid_t child2 = fork();
      if (child2 == 0) {
         int i;
         a = 2;
         for (i = 0; i < 10; i++) {
            printf("Child2 %d\n", a);
            usleep(1);
         }
         return 0;
      }
   }
   int ret;
   while (wait(&ret) != -1);
   return 0;
}

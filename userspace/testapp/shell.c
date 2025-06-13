#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tiny.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syscall.h>

char* origin = "shell"; /* GARBAGE */

char command[256];

char* getcommand()
{
   fgets(command, 256, stdin);
   if (command[0] == EOF) exit(-1);
   command[strlen(command) - 1] = '\0';
   return command;
}

int runcommand(char* cmd)
{
   const char * cmd2 = "pwd";
   if (strstr(cmd, cmd2) == cmd) {
      puts(get_current_dir_name());
      puts("\n");
      return 0;
   }
   const char * cmd3 = "cwd ";
   if (strstr(cmd, cmd3) == cmd) {
      char* param = &cmd[strlen(cmd3)];
      return chdir(param);
   }
   const char * cmd4 = "umask=";
   if (strstr(cmd, cmd4) == cmd) {
      char* param = &cmd[strlen(cmd4)];
      int newmask = atoi(param);
      return umask(newmask);
   }
   const char * cmd5 = "setuid ";
   if (strstr(cmd, cmd5) == cmd) {
      char* param = &cmd[strlen(cmd5)];
      if (setuid(atoi(param)) == -1) {
         puts(strerror(errno));
         puts("\n");
      }
      return 0;
   }
   const char * cmd6 = "setgid ";
   if (strstr(cmd, cmd6) == cmd) {
      char* param = &cmd[strlen(cmd6)];
      if (setgid(atoi(param)) == -1) {
         puts(strerror(errno));
         puts("\n");
      }
      return 0;
   }
   char* myargv[5];
   int myargc = calcargv(cmd, myargv);
   myargv[0] = execpath(getenv("PATH"), myargv[0]);
   pid_t child = fork();
   if (child == 0) {
      execve(myargv[0], myargv, NULL);
      exit(-1);
   } else if(child == -1) {
      puts(strerror(errno));
      puts("\n");
   } else {
      int ret;
      waitpid(child, &ret, 0);
   }
   return 0;
}

int main(int argc, char** argv)
{
   printenv();
   printf("%s\n", getenv("PATH"));
   printf("afds=%p\n", afds);
   printf("environ=%p\n", environ);
   printf("argv=%p\n", argv);
   while (1) {
      printf("%s", "> ");
      char* cmd = getcommand();
      if (strcmp(cmd, "exit") == 0) {
         break;
      }
      runcommand(cmd);
   }
   return 0;
}

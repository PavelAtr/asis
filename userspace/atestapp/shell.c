/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

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
      return 0;
   }
   const char * cmd3 = "cd ";
   if (strstr(cmd, cmd3) == cmd) {
      puts(cmd3);
      char* param = &cmd[strlen(cmd3)];
      int r = chdir(param);
      if (r == -1) {
         printf("chdir error: %s\n", strerror(errno));
         return r;
      }
      setenv("CWD", param, 0);
      return 0;
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
   const char * cmd7 = "env";
   if (strstr(cmd, cmd7) == cmd) {
      printenv();
      return 0;
   }
   char* myargv[5];
   int myargc = calcargv(cmd, myargv);
   pid_t child = fork();
   if (child == 0) {
      execve(myargv[0], myargv, NULL);
      _exit(-1);
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

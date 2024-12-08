#include <stdio.h>
#include <stdlib.h>
#include <tiny.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

char command[256];

int echo = 0;
char ech[2] = {'\0', '\0'};

char* getcommand()
{
  fgets(command, 256, stdin);
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
  const char * cmd3 = "CWD ";
  if (strstr(cmd, cmd3) == cmd) {
    char* param = &cmd[strlen(cmd3)];
    setenv("CWD", param, 0);
    return chdir(param);
  }
  const char * cmd4 = "UMASK=";
  if (strstr(cmd, cmd4) == cmd) {
    char* param = &cmd[strlen(cmd4)];
    int mask = atoi(param);
    setenv("UMASK", param, 0);
    return umask(mask);
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
  } else if(child == -1) {
    puts(strerror(errno));
    puts("\n");
  } else {
    int ret;
    waitpid(child, &ret, 0);
  }
  free(myargv[0]);
  return 0;
}

int main(int argc, char** argv)
{
#ifdef UEFI_KERNEL
  echo = 1;
#else
  echo = 0;
#endif
  int fd;
  if ((fd = open("/dev/tty", O_RDONLY)) == -1)
    return -1;
  if ((fd = open("/dev/tty", O_WRONLY)) == -1)
    return -1;
  if ((fd = open("/dev/tty", O_WRONLY)) == -1)
    return -1;
  stdin = fdopen(0, "r");
  stdout = fdopen(1, "w");
  stderr = fdopen(2, "w");
  setenv("PATH", "/tinysys/:/tinysys/bin/", 0);
  chdir("/tinysys");
  setenv("CWD", "/tinysys", 0);
  umask(0002);
  setenv("UMASK", "0002", 0);
  while (1) {
    puts("> ");
    char* cmd = getcommand();
    if (strcmp(cmd, "exit") == 0) break;
    runcommand(cmd);
  }
  return 0;
}

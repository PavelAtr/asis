#include <unistd.h>

void xexit(int status)
{
   _exit(status);
}

int main(int argc, char** argv)
{
   xexit(5);
}

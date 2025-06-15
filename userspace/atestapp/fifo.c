#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <error.h>
#include <sys/stat.h>


int do_fifo(int argc, char** argv)
{
   mkfifo("fifo", 0660);
   FILE* f1 = fopen("fifo", "w");
   if (!f1) error(errno, errno, "Error fopen fifo %s for writing\n", "fif");
   FILE* f2 = fopen("fifo", "r");
   if (!f2) error(errno, errno, "Error fopen fifo %s for reading\n", "fif");
   printf("Opened fifo for writing: %s %p %d\n", f1->file, ((apipe*)f1)->pbuf, ((apipe*)f1)->pbuf->refcount);
   printf("Opened fifo for reading: %s %p %d\n", f2->file, ((apipe*)f2)->pbuf, ((apipe*)f2)->pbuf->refcount);
   size_t len;
   char buf[100];
   len = fwrite("Hello world!\n\0", 1, 14, f1);
   printf("Wrote to fifo: %ld bytes\n", len);
   fread(buf, 1, len, f2);
   printf("Read from fifo: %s\n", buf);
   return 0;
}

int main(int argc, char** argv) {
   do_fifo(argc, argv);
}

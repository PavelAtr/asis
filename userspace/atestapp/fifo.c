/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <error.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/un.h>


int do_fifo(int argc, char** argv)
{
   mkfifo("fifo", 0660);
   FILE* f1 = fopen("fifo", "w");
   if (!f1) error(errno, errno, "Error fopen fifo %s for writing\n", "fif");
   FILE* f2 = fopen("fifo", "r");
   if (!f2) error(errno, errno, "Error fopen fifo %s for reading\n", "fif");
   printf("Opened fifo for writing: %s %p\n", f1->file, ((anamedpipe*)f1)->pbuf);
   printf("Opened fifo for reading: %s %p\n", f2->file, ((anamedpipe*)f2)->pbuf);
   size_t len;
   char buf[32];
   len = fwrite("Hello world!\0", 1, 13, f1);
   printf("Wrote to fifo: %ld bytes\n", len);
   fread(buf, 1, len, f2);
   printf("Read from fifo: %s\n", buf);
   fclose(f1);
   fclose(f2);
  
   char buf2[32];

   int fd1 = memfd_create("testmem", 0);
   int fd2 = memfd_create("testmem", 0);
   printf("Opened memfd_create %p size=%ld\n", ((amemfile*)afds[fd1])->membuf, afds[fd1]->size);
   printf("Opened memfd_create %p size=%ld\n", ((amemfile*)afds[fd2])->membuf, afds[fd2]->size);
   memcpy(buf2, "Hello world!\0", 13);
   ssize_t ret = write(fd1, buf2, 13);
   printf("Writed memfd_create %p size=%ld\n", ((amemfile*)afds[fd1])->membuf, afds[fd1]->size);
   printf("memfd_create buffer is %s\n", ((amemfile*)afds[fd1])->membuf);
   char buf3[32];
   ssize_t ret2 = read(fd2, buf3, ret);
   printf("Read from memfd_create: %s\n", buf3);
   close(fd1);
   close(fd2);
   
   char buf4[32];
   char* ptr;
   size_t sizeloc;
   FILE * f3 = open_memstream(&ptr, &sizeloc);
   printf("memstream %p\n", ptr);
   len = fwrite("Hello world!\0", 1, 13, f3);
   printf("Wrote to memstream: %ld bytes\n", len);
   printf("memstream %p\n", ptr);
   printf("memstream buffer contain %s\n", ptr);
   fseek(f3, 0, SEEK_SET);
   fread(buf4, 1, len, f3);
   printf("Read from memstream: %s\n", buf4);
   fclose(f3);
   free(ptr);

   char buf5[32];
   char membuf[32];

   FILE* f4 = fmemopen(membuf, 32, "r+");
   len = fwrite("Hello world!\0", 1, 13, f4);
   printf("Wrote to fmemopen: %ld bytes\n", len);
   printf("fmemopen buffer contain %s\n", ((amemfile*)f4)->membuf);
   fseek(f4, 0, SEEK_SET);
   fread(buf5, 1, len, f4);
   printf("Read from fmemopen: %s\n", buf5);

   

   #define SOCKET_PATH "/demo_socket"
   #define BUFFER_SIZE 1024

    int server_socket, client_socket, peer;
    struct sockaddr_un server_address, client_address;
    socklen_t client_address_len;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка при создании сокета\n");
        exit(EXIT_FAILURE);
    }
    // Настройка адреса сокета
    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SOCKET_PATH, sizeof(server_address.sun_path) - 1);

    // Привязка сокета к адресу
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Ошибка при привязке сокета\n");
        exit(EXIT_FAILURE);
    }

    // Прослушивание сокета
    if (listen(server_socket, 5) == -1) {
        perror("Ошибка при прослушивании сокета\n");
        exit(EXIT_FAILURE);
    }

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Ошибка при создании клиентского сокета\n");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сокета
    memset(&client_address, 0, sizeof(client_address));
    client_address.sun_family = AF_UNIX;
    strncpy(client_address.sun_path, SOCKET_PATH, sizeof(client_address.sun_path) - 1);

    // Привязка сокета к адресу
    if (bind(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
        perror("Ошибка при привязке клиентского сокета\n");
        exit(EXIT_FAILURE);
    }

        // Привязка сокета к адресу
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
        perror("Ошибка при коннекте клиентского сокета\n");
        exit(EXIT_FAILURE);
    }
           
    // Приём сокета
    struct sockaddr accept_addr;
    socklen_t accept_addrlen;
    peer = accept(server_socket, &accept_addr, &accept_addrlen);
    if (peer == -1){
        perror("Ошибка приёма соединения\n");
        exit(EXIT_FAILURE);
    }

    printf("peer=%p sock=%p\n",((asocket*)afds[peer])->peer, (asocket*)afds[client_socket]);
    printf("peer=%p sock=%p\n",((asocket*)afds[client_socket])->peer, (asocket*)afds[peer]);

    char buf6[32];
    send(peer, "Hello world!", 13, 0);
    recv(client_socket, buf6, 13, 0);
    printf("Socket client recv %s\n", buf6);

    char buf7[32];
    send(client_socket, "Hello world!", 13, 0);
    recv(peer, buf7, 13, 0);
    printf("Peer recv %s\n", buf7);



   return 0;
}

int main(int argc, char** argv) {
   do_fifo(argc, argv);
}

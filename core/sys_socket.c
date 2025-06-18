/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <asis.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void* sockets[MAXSOCKETS];

int get_free_socket()
{
    for (int i = 0; i < MAXSOCKETS; i++)
    {
        if (!sockets[i])
            return i;
    }
    return -1;
}

int socket_checkperm(const char* path)
{
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      current_errno = ENOENT;
      return -1;
   }
   const char* file = sys_calcpath(mount, path);
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      current_errno = EPERM;
      return -1;
   }
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      current_errno = EPERM;
      return -1;
   }
      struct stat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      current_errno = ENOENT;
      return -1;
   }
   return 0;
}

int sys_listen(void* socket)
{
    int i = get_free_socket();
    if (i == -1)
        return -1;
    asocket* server = socket;    
    sockets[i] = socket;
    if (server->domain == AF_UNIX && server->socktype == SOCK_STREAM) {
        sys_mknod(server->path, S_IFSOCK | 0660);
    }
}

int sys_connect(void* socket, void* saddr)
{
    asocket* client = socket;
    const struct sockaddr *addr = saddr;
    const struct sockaddr_un *un = (const struct sockaddr_un *)addr;
    if (client->domain == AF_UNIX && client->socktype == SOCK_STREAM) {
        asocket* server = NULL;
        for (int i = 0; i < MAXSOCKETS; ++i) {
            if (!sockets[i])
                continue;
            if (((asocket*)sockets[i])->domain == AF_UNIX &&
                ((asocket*)sockets[i])->socktype == SOCK_STREAM)
                if (((asocket*)sockets[i])->bound &&
                    strcmp(((asocket*)sockets[i])->path, un->sun_path) == 0)
			        server = (asocket*)sockets[i];
	    }
	    if (!server) {
	        return -1;
	    }
        if (socket_checkperm(server->path)) {
            return -1;
        }
        if (server->listening && server->num_pending < server->backlog) {
            server->pending[server->num_pending++] = client;
        } else if (!server->listening) {
            server->connected = 1;
            server->peer = client;
        }         
	    return 0;
    }
    return -1;
}
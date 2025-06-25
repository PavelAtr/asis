/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <asis.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

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

errno_t socket_checkperm(const char* path)
{
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      return ENOENT;
   }
   const char* file = sys_calcpath(mount, path);
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      return EPERM;
   }
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      return EPERM;
   }
      struct stat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      return ENOENT;
   }
   return 0;
}

errno_t sys_listen(void* socket)
{
    int i = get_free_socket();
    if (i == -1)
        return ENOMEM;
    asocket* server = socket;    
    sockets[i] = socket;
    if (server->domain == AF_UNIX && server->socktype == SOCK_STREAM) {
        sys_mknod(server->path, S_IFSOCK | 0660);
        sys_printf("sys_mknod(%s)\n", server->path);
        return 0;
    }
    return ENOTSUP;   
}

errno_t sys_connect(void* socket, void* saddr)
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
	        return ENOENT;
	    }
        errno_t err;
        if ((err = socket_checkperm(server->path))) {
            return err;
        }
        if (server->listening && server->num_pending < server->backlog) {
            server->pending[server->num_pending++] = client;
        } else if (!server->listening) {
            server->connected = 1;
            server->peer = client;
        }         
	    return 0;
    }
    return ENOTSUP;
}
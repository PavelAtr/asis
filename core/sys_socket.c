/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <asis.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>

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

int sys_listen(void* socket)
{
    int i = get_free_socket();
    if (i == -1)
        return -1;
    sockets[i] = socket;
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
#ifndef _SYS_UN_H
#define _SYS_UN_H

#define UNIX_PATH_MAX   108

struct sockaddr_un {
        int sun_family; /* AF_UNIX */
        char sun_path[UNIX_PATH_MAX];   /* pathname */
};


#endif
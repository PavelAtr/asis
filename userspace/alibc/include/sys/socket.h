/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#include <sys/types.h>

typedef unsigned int socklen_t;
typedef unsigned short sa_family_t;

struct sockaddr {
  sa_family_t     sa_family;      /* Address family */
  char            sa_data[];      /* Socket address */
};

struct sockaddr_storage {
  sa_family_t     ss_family;      /* Address family */
};

int socket(int domain, int type, int protocol);

#define PF_UNSPEC	0	/* Unspecified.  */
#define PF_LOCAL	1	/* Local to host (pipes and file-domain).  */
#define PF_UNIX		PF_LOCAL /* POSIX name for PF_LOCAL.  */
#define PF_FILE		PF_LOCAL /* Another non-standard name for PF_LOCAL.  */
#define PF_INET		2	/* IP protocol family.  */
#define PF_AX25		3	/* Amateur Radio AX.25.  */
#define PF_IPX		4	/* Novell Internet Protocol.  */
#define PF_APPLETALK	5	/* Appletalk DDP.  */
#define PF_NETROM	6	/* Amateur radio NetROM.  */
#define PF_BRIDGE	7	/* Multiprotocol bridge.  */
#define PF_ATMPVC	8	/* ATM PVCs.  */
#define PF_X25		9	/* Reserved for X.25 project.  */
#define PF_INET6	10	/* IP version 6.  */
#define PF_ROSE		11	/* Amateur Radio X.25 PLP.  */
#define PF_DECnet	12	/* Reserved for DECnet project.  */
#define PF_NETBEUI	13	/* Reserved for 802.2LLC project.  */
#define PF_SECURITY	14	/* Security callback pseudo AF.  */
#define PF_KEY		15	/* PF_KEY key management API.  */
#define PF_NETLINK	16
#define PF_ROUTE	PF_NETLINK /* Alias to emulate 4.4BSD.  */
#define PF_PACKET	17	/* Packet family.  */
#define PF_ASH		18	/* Ash.  */
#define PF_ECONET	19	/* Acorn Econet.  */
#define PF_ATMSVC	20	/* ATM SVCs.  */
#define PF_RDS		21	/* RDS sockets.  */
#define PF_SNA		22	/* Linux SNA Project */
#define PF_IRDA		23	/* IRDA sockets.  */
#define PF_PPPOX	24	/* PPPoX sockets.  */
#define PF_WANPIPE	25	/* Wanpipe API sockets.  */
#define PF_LLC		26	/* Linux LLC.  */
#define PF_IB		27	/* Native InfiniBand address.  */
#define PF_MPLS		28	/* MPLS.  */
#define PF_CAN		29	/* Controller Area Network.  */
#define PF_TIPC		30	/* TIPC sockets.  */
#define PF_BLUETOOTH	31	/* Bluetooth sockets.  */
#define PF_IUCV		32	/* IUCV sockets.  */
#define PF_RXRPC	33	/* RxRPC sockets.  */
#define PF_ISDN		34	/* mISDN sockets.  */
#define PF_PHONET	35	/* Phonet sockets.  */
#define PF_IEEE802154	36	/* IEEE 802.15.4 sockets.  */
#define PF_CAIF		37	/* CAIF sockets.  */
#define PF_ALG		38	/* Algorithm sockets.  */
#define PF_NFC		39	/* NFC sockets.  */
#define PF_VSOCK	40	/* vSockets.  */
#define PF_KCM		41	/* Kernel Connection Multiplexor.  */
#define PF_QIPCRTR	42	/* Qualcomm IPC Router.  */
#define PF_SMC		43	/* SMC sockets.  */
#define PF_XDP		44	/* XDP sockets.  */
#define PF_MCTP		45	/* Management component transport protocol.  */
#define PF_MAX		46	/* For now..  */
#define AF_UNSPEC	PF_UNSPEC
#define AF_LOCAL	PF_LOCAL
#define AF_UNIX		PF_UNIX
#define AF_FILE		PF_FILE
#define AF_INET		PF_INET
#define AF_AX25		PF_AX25
#define AF_IPX		PF_IPX
#define AF_APPLETALK	PF_APPLETALK
#define AF_NETROM	PF_NETROM
#define AF_BRIDGE	PF_BRIDGE
#define AF_ATMPVC	PF_ATMPVC
#define AF_X25		PF_X25
#define AF_INET6	PF_INET6
#define AF_ROSE		PF_ROSE
#define AF_DECnet	PF_DECnet
#define AF_NETBEUI	PF_NETBEUI
#define AF_SECURITY	PF_SECURITY
#define AF_KEY		PF_KEY
#define AF_NETLINK	PF_NETLINK
#define AF_ROUTE	PF_ROUTE
#define AF_PACKET	PF_PACKET
#define AF_ASH		PF_ASH
#define AF_ECONET	PF_ECONET
#define AF_ATMSVC	PF_ATMSVC
#define AF_RDS		PF_RDS
#define AF_SNA		PF_SNA
#define AF_IRDA		PF_IRDA
#define AF_PPPOX	PF_PPPOX
#define AF_WANPIPE	PF_WANPIPE
#define AF_LLC		PF_LLC
#define AF_IB		PF_IB
#define AF_MPLS		PF_MPLS
#define AF_CAN		PF_CAN
#define AF_TIPC		PF_TIPC
#define AF_BLUETOOTH	PF_BLUETOOTH
#define AF_IUCV		PF_IUCV
#define AF_RXRPC	PF_RXRPC
#define AF_ISDN		PF_ISDN
#define AF_PHONET	PF_PHONET
#define AF_IEEE802154	PF_IEEE802154
#define AF_CAIF		PF_CAIF
#define AF_ALG		PF_ALG
#define AF_NFC		PF_NFC
#define AF_VSOCK	PF_VSOCK
#define AF_KCM		PF_KCM
#define AF_QIPCRTR	PF_QIPCRTR
#define AF_SMC		PF_SMC
#define AF_XDP		PF_XDP
#define AF_MCTP		PF_MCTP
#define AF_MAX		PF_MAX

#define   SOCK_STREAM   1  /* Provides sequenced, reliable, two-way, connection-based byte streams.  An out-of-band data transmission mechanism may be supported. */
#define   SOCK_DGRAM    2  /* Supports datagrams (connectionless, unreliable messages of a fixed maximum length). */
#define   SOCK_SEQPACKET 3  /* Provides a sequenced, reliable, two-way connection-based data transmission path for datagrams of fixed maximum length; a consumer is required to  read  an  entire
                       packet with each input system call. */
#define   SOCK_RAW 4       /* Provides raw network protocol access. */
#define   SOCK_RDM 5         /* Provides a reliable datagram layer that does not guarantee ordering. */
#define   SOCK_PACKET 6      /* Obsolete and should not be used in new programs; see packet(7). */


#define   SOCK_NONBLOCK 7   /* Set the O_NONBLOCK file status flag on the open file description (see open(2)) referred to by the new file descriptor.  Using this flag saves extra calls  to  fc‐
                       ntl(2) to achieve the same result. */
#define   SOCK_CLOEXEC 8

int getsockopt(int sockfd, int level, int optname, void* optval, socklen_t* optlen);
int setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen);

/* For setsockopt(2) */
#define SOL_SOCKET      1

#define SO_DEBUG	1
#define SO_REUSEADDR	2
#define SO_TYPE		3
#define SO_ERROR	4
#define SO_DONTROUTE	5
#define SO_BROADCAST	6
#define SO_SNDBUF	7
#define SO_RCVBUF	8
#define SO_SNDBUFFORCE	32
#define SO_RCVBUFFORCE	33
#define SO_KEEPALIVE	9
#define SO_OOBINLINE	10
#define SO_NO_CHECK	11
#define SO_PRIORITY	12
#define SO_LINGER	13
#define SO_BSDCOMPAT	14
#define SO_REUSEPORT	15
#define SO_PASSCRED	16
#define SO_PEERCRED	17
#define SO_RCVLOWAT	18
#define SO_SNDLOWAT	19
#define SO_RCVTIMEO_OLD	20
#define SO_SNDTIMEO_OLD	21
#define SO_SECURITY_AUTHENTICATION		22
#define SO_SECURITY_ENCRYPTION_TRANSPORT	23
#define SO_SECURITY_ENCRYPTION_NETWORK		24
#define SO_BINDTODEVICE	25
#define SO_ATTACH_FILTER	26
#define SO_DETACH_FILTER	27
#define SO_GET_FILTER		SO_ATTACH_FILTER
#define SO_PEERNAME		28
#define SO_ACCEPTCONN		30
#define SO_PEERSEC		31
#define SO_PASSSEC		34
#define SO_MARK			36
#define SO_PROTOCOL		38
#define SO_DOMAIN		39
#define SO_RXQ_OVFL             40
#define SO_WIFI_STATUS		41
#define SCM_WIFI_STATUS	SO_WIFI_STATUS
#define SO_PEEK_OFF		42
#define SO_NOFCS		43
#define SO_LOCK_FILTER		44
#define SO_SELECT_ERR_QUEUE	45
#define SO_BUSY_POLL		46
#define SO_MAX_PACING_RATE	47
#define SO_BPF_EXTENSIONS	48
#define SO_INCOMING_CPU		49
#define SO_ATTACH_BPF		50
#define SO_DETACH_BPF		SO_DETACH_FILTER
#define SO_ATTACH_REUSEPORT_CBPF	51
#define SO_ATTACH_REUSEPORT_EBPF	52
#define SO_CNX_ADVICE		53
#define SO_MEMINFO		55
#define SO_INCOMING_NAPI_ID	56
#define SO_COOKIE		57
#define SO_PEERGROUPS		59
#define SO_ZEROCOPY		60
#define SO_TXTIME		61
#define SCM_TXTIME		SO_TXTIME
#define SO_BINDTOIFINDEX	62
#define SO_TIMESTAMP_OLD        29
#define SO_TIMESTAMPNS_OLD      35
#define SO_TIMESTAMPING_OLD     37
#define SO_TIMESTAMP_NEW        63
#define SO_TIMESTAMPNS_NEW      64
#define SO_TIMESTAMPING_NEW     65
#define SO_RCVTIMEO_NEW         66
#define SO_SNDTIMEO_NEW         67
#define SO_DETACH_REUSEPORT_BPF 68
#define SO_PREFER_BUSY_POLL	69
#define SO_BUSY_POLL_BUDGET	70
#define SO_NETNS_COOKIE		71
#define SO_BUF_LOCK		72
#define SO_RESERVE_MEM		73
#define SO_TXREHASH		74
#define SO_RCVMARK		75
#define SO_PASSPIDFD		76
#define SO_PEERPIDFD		77
#define SO_TIMESTAMP		SO_TIMESTAMP_OLD
#define SO_TIMESTAMPNS		SO_TIMESTAMPNS_OLD
#define SO_TIMESTAMPING		SO_TIMESTAMPING_OLD
#define SO_RCVTIMEO		SO_RCVTIMEO_OLD
#define SO_SNDTIMEO		SO_SNDTIMEO_OLD
#define SCM_TIMESTAMP           SO_TIMESTAMP
#define SCM_TIMESTAMPNS         SO_TIMESTAMPNS
#define SCM_TIMESTAMPING        SO_TIMESTAMPING

int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);

int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);

int shutdown(int sockfd, int how);

/* The following constants should be used for the second parameter of
   `shutdown'.  */
enum
{
  SHUT_RD = 0,          /* No more receptions.  */
#define SHUT_RD         SHUT_RD
  SHUT_WR,              /* No more transmissions.  */
#define SHUT_WR         SHUT_WR
  SHUT_RDWR             /* No more receptions or transmissions.  */
#define SHUT_RDWR       SHUT_RDWR
};

/* Structure describing messages sent by
   `sendmsg' and received by `recvmsg'.  */
struct msghdr
  {
    void *msg_name;             /* Address to send to/receive from.  */
    socklen_t msg_namelen;      /* Length of address data.  */

    struct iovec *msg_iov;      /* Vector of data to send/receive into.  */
    size_t msg_iovlen;          /* Number of elements in the vector.  */

    void *msg_control;          /* Ancillary data (eg BSD filedesc passing). */
    size_t msg_controllen;      /* Ancillary data buffer length.
                                   !! The type should be socklen_t but the
                                   definition of the kernel is incompatible
                                   with this.  */

    int msg_flags;              /* Flags on received message.  */
  };

struct cmsghdr
  {
    size_t cmsg_len;            /* Length of data in cmsg_data plus length
                                   of cmsghdr structure.
                                   !! The type should be socklen_t but the
                                   definition of the kernel is incompatible
                                   with this.  */
    int cmsg_level;             /* Originating protocol.  */
    int cmsg_type;              /* Protocol specific type.  */
  };

struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
                                      struct cmsghdr *__cmsg);

#define CMSG_DATA(cmsg) ((unsigned char *) ((struct cmsghdr *) (cmsg) + 1))
#define CMSG_NXTHDR(mhdr, cmsg) __cmsg_nxthdr (mhdr, cmsg)
#define CMSG_FIRSTHDR(mhdr) \
  ((size_t) (mhdr)->msg_controllen >= sizeof (struct cmsghdr)                 \
   ? (struct cmsghdr *) (mhdr)->msg_control : (struct cmsghdr *) 0)
#define CMSG_ALIGN(len) (((len) + sizeof (size_t) - 1) \
                         & (size_t) ~(sizeof (size_t) - 1))
#define CMSG_SPACE(len) (CMSG_ALIGN (len) \
                         + CMSG_ALIGN (sizeof (struct cmsghdr)))
#define CMSG_LEN(len)   (CMSG_ALIGN (sizeof (struct cmsghdr)) + (len))

struct ucred
{
  pid_t pid;                    /* PID of sending process.  */
  uid_t uid;                    /* UID of sending process.  */
  gid_t gid;                    /* GID of sending process.  */
};

enum
  {
    SCM_RIGHTS = 0x01           /* Transfer file descriptors.  */
#define SCM_RIGHTS SCM_RIGHTS
#ifdef __USE_GNU
    , SCM_CREDENTIALS = 0x02    /* Credentials passing.  */
# define SCM_CREDENTIALS SCM_CREDENTIALS
#endif
  };

/* Bits in the FLAGS argument to `send', `recv', et al.  */
enum
  {
    MSG_OOB             = 0x01, /* Process out-of-band data.  */
#define MSG_OOB         MSG_OOB
    MSG_PEEK            = 0x02, /* Peek at incoming messages.  */
#define MSG_PEEK        MSG_PEEK
    MSG_DONTROUTE       = 0x04, /* Don't use local routing.  */
#define MSG_DONTROUTE   MSG_DONTROUTE
#ifdef __USE_GNU
    /* DECnet uses a different name.  */
    MSG_TRYHARD         = MSG_DONTROUTE,
# define MSG_TRYHARD    MSG_DONTROUTE
#endif
    MSG_CTRUNC          = 0x08, /* Control data lost before delivery.  */
#define MSG_CTRUNC      MSG_CTRUNC
    MSG_PROXY           = 0x10, /* Supply or ask second address.  */
#define MSG_PROXY       MSG_PROXY
    MSG_TRUNC           = 0x20,
#define MSG_TRUNC       MSG_TRUNC
    MSG_DONTWAIT        = 0x40, /* Nonblocking IO.  */
#define MSG_DONTWAIT    MSG_DONTWAIT
    MSG_EOR             = 0x80, /* End of record.  */
#define MSG_EOR         MSG_EOR
    MSG_WAITALL         = 0x100, /* Wait for a full request.  */
#define MSG_WAITALL     MSG_WAITALL
    MSG_FIN             = 0x200,
#define MSG_FIN         MSG_FIN
    MSG_SYN             = 0x400,
#define MSG_SYN         MSG_SYN
    MSG_CONFIRM         = 0x800, /* Confirm path validity.  */
#define MSG_CONFIRM     MSG_CONFIRM
    MSG_RST             = 0x1000,
#define MSG_RST         MSG_RST
    MSG_ERRQUEUE        = 0x2000, /* Fetch message from error queue.  */
#define MSG_ERRQUEUE    MSG_ERRQUEUE
    MSG_NOSIGNAL        = 0x4000, /* Do not generate SIGPIPE.  */
#define MSG_NOSIGNAL    MSG_NOSIGNAL
    MSG_MORE            = 0x8000,  /* Sender will send more.  */
#define MSG_MORE        MSG_MORE
    MSG_WAITFORONE      = 0x10000, /* Wait for at least one packet to return.*/
#define MSG_WAITFORONE  MSG_WAITFORONE
    MSG_BATCH           = 0x40000, /* sendmmsg: more messages coming.  */
#define MSG_BATCH       MSG_BATCH
    MSG_ZEROCOPY        = 0x4000000, /* Use user data in kernel path.  */
#define MSG_ZEROCOPY    MSG_ZEROCOPY
    MSG_FASTOPEN        = 0x20000000, /* Send data in TCP SYN.  */
#define MSG_FASTOPEN    MSG_FASTOPEN

    MSG_CMSG_CLOEXEC    = 0x40000000    /* Set close_on_exit for file
                                           descriptor received through
                                           SCM_RIGHTS.  */
#define MSG_CMSG_CLOEXEC MSG_CMSG_CLOEXEC
  };


int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr* addr,
                  socklen_t* addrlen);
int getsockname(int sockfd, struct sockaddr * addr,
                       socklen_t* addrlen);

ssize_t send(int sockfd, const void* buf, size_t len, int flags);
/*ssize_t sendto(int sockfd, const void* buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen);*/

ssize_t recv(int sockfd, void* buf, size_t len, int flags);
/*ssize_t recvfrom(int sockfd, void* buf, size_t len,
                int flags, struct sockaddr* src_addr,
                socklen_t* addrlen);*/
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
                                      struct cmsghdr *__cmsg);

int socketpair(int domain, int type, int protocol, int sv[2]);

#endif

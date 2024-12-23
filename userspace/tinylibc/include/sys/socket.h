#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

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

#define       AF_UNIX      1 /* Local communication */
#define       AF_LOCAL     2 /* Synonym for AF_UNIX  */
#define       AF_INET      3 /* IPv4 Internet protocols                    ip(7) */
#define       AF_AX25      4 /* Amateur radio AX.25 protocol               ax25(4) */
#define       AF_IPX       5 /* IPX - Novell protocols  */
#define       AF_APPLETALK 6 /* /AppleTalk                                  ddp(7) */
#define       AF_X25       7 /* ITU-T X.25 / ISO-8208 protocol             x25(7) */
#define       AF_INET6     8 /* IPv6 Internet protocols                    ipv6(7) */
#define       AF_DECnet    9 /* DECet protocol sockets */
#define       AF_KEY       10 /* Key  management protocol, originally developed for usage with IPsec */
#define       AF_NETLINK   11 /* Kernel user interface device               netlink(7) */
#define       AF_PACKET    12 /* Low-level packet interface                 packet(7) */
#define       AF_RDS       13 /* Reliable Datagram Sockets (RDS) protocol   rds(7) rds-rdma(7) */
#define       AF_PPPOX     14 /* Generic PPP transport layer, for setting up L2 tunnels (L2TP and PPPoE) */
#define       AF_LLC       15 /* Logical  link  control  (IEEE 802.2 LLC) protocol */
#define       AF_IB        16 /* InfiniBand native addressing */
#define       AF_MPLS      17 /* Multiprotocol Label Switching */
#define       AF_CAN       18 /* Controller Area Network  automotive  bus protocol */
#define       AF_TIPC      19 /* TIPC, "cluster domain sockets" protocol */
#define       AF_BLUETOOTH 20 /* Bluetooth low-level socket protocol */
#define       AF_ALG       21 /* Interface to kernel crypto API */
#define       AF_VSOCK     22 /* VSOCK   (originally  "VMWare  VSockets")   vsock(7) protocol for hypervisor-guest communication */
#define       AF_KCM       23 /* KCM  (kernel connection multiplexer) interface */
#define       AF_XDP       24 /* XDP (express data path) interface */

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

#endif


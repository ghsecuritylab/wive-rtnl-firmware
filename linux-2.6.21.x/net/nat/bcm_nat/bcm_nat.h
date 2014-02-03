#ifndef _BCM_NAT_WANTED
#define _BCM_NAT_WANTED

#include <net/ip.h>
#include <net/route.h>
#include <net/neighbour.h>

//#define DEBUG

/*
 * fastnat must full skip not ipv4 and mcast/bcast traffic
 */
#define FASTNAT_SKIP_TYPE(pf)	(pf != PF_INET || (*pskb)->pkt_type == PACKET_BROADCAST || (*pskb)->pkt_type == PACKET_MULTICAST)

/*
 * cb fastforward flag  hwnat use 10+6 offset - fastroute 10+6+2
 */
#define NF_FAST_ROUTE		17

/*
 * conntrack fastforward flags
 * please undefine NF_STOP in linux/netfilter.h if fastnat use
 */
#define	NF_FAST_NAT_DENY	1
#define NF_FAST_NAT		5
#define NF_STOP			6

extern int nf_conntrack_fastnat;
extern int nf_conntrack_fastroute;

extern int nf_ct_ipv4_gather_frags(struct sk_buff *skb, u_int32_t user);
extern int ip_rcv_finish(struct sk_buff *skb);
#endif

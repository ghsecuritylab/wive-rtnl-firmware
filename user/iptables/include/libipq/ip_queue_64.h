/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
/* Redefine everything for a 64-bit kernel on 32-bit userspace */

/* Based on ip_queue.h by (C) 2000 James Morris, this code is GPL. */
#ifndef _IP_QUEUE_H
#define _IP_QUEUE_H

#include <net/if.h>
#include <sys/types.h>

/* Messages sent from kernel */
typedef struct ipq_packet_msg {
	u_int64_t packet_id;	/* ID of queued packet */
	u_int64_t mark;		/* Netfilter mark value */
	int64_t timestamp_sec;	/* Packet arrival time (seconds) */
	int64_t timestamp_usec;	/* Packet arrvial time (+useconds) */
	unsigned int hook;		/* Netfilter hook we rode in on */
	char indev_name[IFNAMSIZ];	/* Name of incoming interface */
	char outdev_name[IFNAMSIZ];	/* Name of outgoing interface */
	unsigned short hw_protocol;	/* Hardware protocol (network order) */
	unsigned short hw_type;		/* Hardware type */
	unsigned char hw_addrlen;	/* Hardware address length */
	unsigned char hw_addr[8];	/* Hardware address */
	u_int64_t data_len;		/* Length of packet data */
	unsigned char payload[0];	/* Optional packet data */
} ipq_packet_msg_t;

/* Messages sent from userspace */
typedef struct ipq_mode_msg {
	unsigned char value;		/* Requested mode */
	u_int64_t range;		/* Optional range of packet requested */
} ipq_mode_msg_t;

typedef struct ipq_verdict_msg {
	unsigned int value;		/* Verdict to hand to netfilter */
	u_int64_t id;		/* Packet ID for this verdict */
	u_int64_t data_len;		/* Length of replacement data */
	unsigned char payload[0];	/* Optional replacement packet */
} ipq_verdict_msg_t;

typedef struct ipq_peer_msg {
	union {
		ipq_verdict_msg_t verdict;
		ipq_mode_msg_t mode;
	} msg;
} ipq_peer_msg_t;

/* Packet delivery modes */
enum {
	IPQ_COPY_NONE,		/* Initial mode, packets are dropped */
	IPQ_COPY_META,		/* Copy metadata */
	IPQ_COPY_PACKET		/* Copy metadata + packet (range) */
};
#define IPQ_COPY_MAX IPQ_COPY_PACKET

/* Types of messages */
#define IPQM_BASE	0x10	/* standard netlink messages below this */
#define IPQM_MODE	(IPQM_BASE + 1)		/* Mode request from peer */
#define IPQM_VERDICT	(IPQM_BASE + 2)		/* Verdict from peer */ 
#define IPQM_PACKET	(IPQM_BASE + 3)		/* Packet from kernel */
#define IPQM_MAX	(IPQM_BASE + 4)

#endif /*_IP_QUEUE_H*/

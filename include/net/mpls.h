extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
/*
 * Copyright (c) 2014 Nicira, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */

#ifndef _NET_MPLS_H
#define _NET_MPLS_H 1

#include <linux/if_ether.h>
#include <linux/netdevice.h>

#define MPLS_HLEN 4

struct mpls_shim_hdr {
	__be32 label_stack_entry;
};

static inline bool eth_p_mpls(__be16 eth_type)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/mpls.h: line 32 \n"); 
	return eth_type == htons(ETH_P_MPLS_UC) ||
		eth_type == htons(ETH_P_MPLS_MC);
}

static inline struct mpls_shim_hdr *mpls_hdr(const struct sk_buff *skb)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/mpls.h: line 39 \n"); 
	return (struct mpls_shim_hdr *)skb_network_header(skb);
}
#endif

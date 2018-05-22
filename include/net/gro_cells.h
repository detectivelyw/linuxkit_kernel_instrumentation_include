extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _NET_GRO_CELLS_H
#define _NET_GRO_CELLS_H

#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/netdevice.h>

struct gro_cell {
	struct sk_buff_head	napi_skbs;
	struct napi_struct	napi;
};

struct gro_cells {
	struct gro_cell __percpu	*cells;
};

static inline int gro_cells_receive(struct gro_cells *gcells, struct sk_buff *skb)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/gro_cells.h: line 23 \n"); 
	struct gro_cell *cell;
	struct net_device *dev = skb->dev;

	if (!gcells->cells || skb_cloned(skb) || !(dev->features & NETIF_F_GRO))
		return netif_rx(skb);

	cell = this_cpu_ptr(gcells->cells);

	if (skb_queue_len(&cell->napi_skbs) > netdev_max_backlog) {
		atomic_long_inc(&dev->rx_dropped);
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	__skb_queue_tail(&cell->napi_skbs, skb);
	if (skb_queue_len(&cell->napi_skbs) == 1)
		napi_schedule(&cell->napi);
	return NET_RX_SUCCESS;
}

/* called under BH context */
static inline int gro_cell_poll(struct napi_struct *napi, int budget)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/gro_cells.h: line 47 \n"); 
	struct gro_cell *cell = container_of(napi, struct gro_cell, napi);
	struct sk_buff *skb;
	int work_done = 0;

	while (work_done < budget) {
		skb = __skb_dequeue(&cell->napi_skbs);
		if (!skb)
			break;
		napi_gro_receive(napi, skb);
		work_done++;
	}

	if (work_done < budget)
		napi_complete_done(napi, work_done);
	return work_done;
}

static inline int gro_cells_init(struct gro_cells *gcells, struct net_device *dev)
{
	int i;

	gcells->cells = alloc_percpu(struct gro_cell);
	if (!gcells->cells)
		return -ENOMEM;

	for_each_possible_cpu(i) {
		struct gro_cell *cell = per_cpu_ptr(gcells->cells, i);

		__skb_queue_head_init(&cell->napi_skbs);

		set_bit(NAPI_STATE_NO_BUSY_POLL, &cell->napi.state);

		netif_napi_add(dev, &cell->napi, gro_cell_poll, 64);
		napi_enable(&cell->napi);
	}
	return 0;
}

static inline void gro_cells_destroy(struct gro_cells *gcells)
{
	int i;

	if (!gcells->cells)
		return;
	for_each_possible_cpu(i) {
		struct gro_cell *cell = per_cpu_ptr(gcells->cells, i);

		netif_napi_del(&cell->napi);
		__skb_queue_purge(&cell->napi_skbs);
	}
	free_percpu(gcells->cells);
	gcells->cells = NULL;
}

#endif

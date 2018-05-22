extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef __SEQ_FILE_NET_H__
#define __SEQ_FILE_NET_H__

#include <linux/seq_file.h>

struct net;
extern struct net init_net;

struct seq_net_private {
#ifdef CONFIG_NET_NS
	struct net *net;
#endif
};

int seq_open_net(struct inode *, struct file *,
		 const struct seq_operations *, int);
int single_open_net(struct inode *, struct file *file,
		int (*show)(struct seq_file *, void *));
int seq_release_net(struct inode *, struct file *);
int single_release_net(struct inode *, struct file *);
static inline struct net *seq_file_net(struct seq_file *seq)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/seq_file_net.h: line 27 \n"); 
#ifdef CONFIG_NET_NS
	return ((struct seq_net_private *)seq->private)->net;
#else
	return &init_net;
#endif
}

#endif

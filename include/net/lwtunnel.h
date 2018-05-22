extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef __NET_LWTUNNEL_H
#define __NET_LWTUNNEL_H 1

#include <linux/lwtunnel.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <net/route.h>

#define LWTUNNEL_HASH_BITS   7
#define LWTUNNEL_HASH_SIZE   (1 << LWTUNNEL_HASH_BITS)

/* lw tunnel state flags */
#define LWTUNNEL_STATE_OUTPUT_REDIRECT	BIT(0)
#define LWTUNNEL_STATE_INPUT_REDIRECT	BIT(1)
#define LWTUNNEL_STATE_XMIT_REDIRECT	BIT(2)

enum {
	LWTUNNEL_XMIT_DONE,
	LWTUNNEL_XMIT_CONTINUE,
};


struct lwtunnel_state {
	__u16		type;
	__u16		flags;
	atomic_t	refcnt;
	int		(*orig_output)(struct net *net, struct sock *sk, struct sk_buff *skb);
	int		(*orig_input)(struct sk_buff *);
	int             len;
	__u16		headroom;
	__u8            data[0];
};

struct lwtunnel_encap_ops {
	int (*build_state)(struct net_device *dev, struct nlattr *encap,
			   unsigned int family, const void *cfg,
			   struct lwtunnel_state **ts);
	int (*output)(struct net *net, struct sock *sk, struct sk_buff *skb);
	int (*input)(struct sk_buff *skb);
	int (*fill_encap)(struct sk_buff *skb,
			  struct lwtunnel_state *lwtstate);
	int (*get_encap_size)(struct lwtunnel_state *lwtstate);
	int (*cmp_encap)(struct lwtunnel_state *a, struct lwtunnel_state *b);
	int (*xmit)(struct sk_buff *skb);

	struct module *owner;
};

#ifdef CONFIG_LWTUNNEL
void lwtstate_free(struct lwtunnel_state *lws);

static inline struct lwtunnel_state *
lwtstate_get(struct lwtunnel_state *lws)
{
	if (lws)
		atomic_inc(&lws->refcnt);

	return lws;
}

static inline void lwtstate_put(struct lwtunnel_state *lws)
{
	if (!lws)
		return;

	if (atomic_dec_and_test(&lws->refcnt))
		lwtstate_free(lws);
}

static inline bool lwtunnel_output_redirect(struct lwtunnel_state *lwtstate)
{
	if (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_OUTPUT_REDIRECT))
		return true;

	return false;
}

static inline bool lwtunnel_input_redirect(struct lwtunnel_state *lwtstate)
{
	if (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_INPUT_REDIRECT))
		return true;

	return false;
}

static inline bool lwtunnel_xmit_redirect(struct lwtunnel_state *lwtstate)
{
	if (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_XMIT_REDIRECT))
		return true;

	return false;
}

static inline unsigned int lwtunnel_headroom(struct lwtunnel_state *lwtstate,
					     unsigned int mtu)
{
	if (lwtunnel_xmit_redirect(lwtstate) && lwtstate->headroom < mtu)
		return lwtstate->headroom;

	return 0;
}

int lwtunnel_encap_add_ops(const struct lwtunnel_encap_ops *op,
			   unsigned int num);
int lwtunnel_encap_del_ops(const struct lwtunnel_encap_ops *op,
			   unsigned int num);
int lwtunnel_valid_encap_type(u16 encap_type);
int lwtunnel_valid_encap_type_attr(struct nlattr *attr, int len);
int lwtunnel_build_state(struct net_device *dev, u16 encap_type,
			 struct nlattr *encap,
			 unsigned int family, const void *cfg,
			 struct lwtunnel_state **lws);
int lwtunnel_fill_encap(struct sk_buff *skb,
			struct lwtunnel_state *lwtstate);
int lwtunnel_get_encap_size(struct lwtunnel_state *lwtstate);
struct lwtunnel_state *lwtunnel_state_alloc(int hdr_len);
int lwtunnel_cmp_encap(struct lwtunnel_state *a, struct lwtunnel_state *b);
int lwtunnel_output(struct net *net, struct sock *sk, struct sk_buff *skb);
int lwtunnel_input(struct sk_buff *skb);
int lwtunnel_xmit(struct sk_buff *skb);

#else

static inline void lwtstate_free(struct lwtunnel_state *lws)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 131 \n"); 
}

static inline struct lwtunnel_state *
lwtstate_get(struct lwtunnel_state *lws)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 137 \n"); 
	return lws;
}

static inline void lwtstate_put(struct lwtunnel_state *lws)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 143 \n"); 
}

static inline bool lwtunnel_output_redirect(struct lwtunnel_state *lwtstate)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 148 \n"); 
	return false;
}

static inline bool lwtunnel_input_redirect(struct lwtunnel_state *lwtstate)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 154 \n"); 
	return false;
}

static inline bool lwtunnel_xmit_redirect(struct lwtunnel_state *lwtstate)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 160 \n"); 
	return false;
}

static inline unsigned int lwtunnel_headroom(struct lwtunnel_state *lwtstate,
					     unsigned int mtu)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 167 \n"); 
	return 0;
}

static inline int lwtunnel_encap_add_ops(const struct lwtunnel_encap_ops *op,
					 unsigned int num)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 174 \n"); 
	return -EOPNOTSUPP;

}

static inline int lwtunnel_encap_del_ops(const struct lwtunnel_encap_ops *op,
					 unsigned int num)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 182 \n"); 
	return -EOPNOTSUPP;
}

static inline int lwtunnel_valid_encap_type(u16 encap_type)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 188 \n"); 
	return -EOPNOTSUPP;
}
static inline int lwtunnel_valid_encap_type_attr(struct nlattr *attr, int len)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 193 \n"); 
	/* return 0 since we are not walking attr looking for
	 * RTA_ENCAP_TYPE attribute on nexthops.
	 */
	return 0;
}

static inline int lwtunnel_build_state(struct net_device *dev, u16 encap_type,
				       struct nlattr *encap,
				       unsigned int family, const void *cfg,
				       struct lwtunnel_state **lws)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 205 \n"); 
	return -EOPNOTSUPP;
}

static inline int lwtunnel_fill_encap(struct sk_buff *skb,
				      struct lwtunnel_state *lwtstate)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 212 \n"); 
	return 0;
}

static inline int lwtunnel_get_encap_size(struct lwtunnel_state *lwtstate)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 218 \n"); 
	return 0;
}

static inline struct lwtunnel_state *lwtunnel_state_alloc(int hdr_len)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 224 \n"); 
	return NULL;
}

static inline int lwtunnel_cmp_encap(struct lwtunnel_state *a,
				     struct lwtunnel_state *b)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 231 \n"); 
	return 0;
}

static inline int lwtunnel_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 237 \n"); 
	return -EOPNOTSUPP;
}

static inline int lwtunnel_input(struct sk_buff *skb)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 243 \n"); 
	return -EOPNOTSUPP;
}

static inline int lwtunnel_xmit(struct sk_buff *skb)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/lwtunnel.h: line 249 \n"); 
	return -EOPNOTSUPP;
}

#endif /* CONFIG_LWTUNNEL */

#define MODULE_ALIAS_RTNL_LWT(encap_type) MODULE_ALIAS("rtnl-lwt-" __stringify(encap_type))

#endif /* __NET_LWTUNNEL_H */

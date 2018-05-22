extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef __NET_FIB_RULES_H
#define __NET_FIB_RULES_H

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/netdevice.h>
#include <linux/fib_rules.h>
#include <net/flow.h>
#include <net/rtnetlink.h>

struct fib_rule {
	struct list_head	list;
	int			iifindex;
	int			oifindex;
	u32			mark;
	u32			mark_mask;
	u32			flags;
	u32			table;
	u8			action;
	u8			l3mdev;
	/* 2 bytes hole, try to use */
	u32			target;
	__be64			tun_id;
	struct fib_rule __rcu	*ctarget;
	struct net		*fr_net;

	atomic_t		refcnt;
	u32			pref;
	int			suppress_ifgroup;
	int			suppress_prefixlen;
	char			iifname[IFNAMSIZ];
	char			oifname[IFNAMSIZ];
	struct rcu_head		rcu;
};

struct fib_lookup_arg {
	void			*lookup_ptr;
	void			*result;
	struct fib_rule		*rule;
	u32			table;
	int			flags;
#define FIB_LOOKUP_NOREF		1
#define FIB_LOOKUP_IGNORE_LINKSTATE	2
};

struct fib_rules_ops {
	int			family;
	struct list_head	list;
	int			rule_size;
	int			addr_size;
	int			unresolved_rules;
	int			nr_goto_rules;

	int			(*action)(struct fib_rule *,
					  struct flowi *, int,
					  struct fib_lookup_arg *);
	bool			(*suppress)(struct fib_rule *,
					    struct fib_lookup_arg *);
	int			(*match)(struct fib_rule *,
					 struct flowi *, int);
	int			(*configure)(struct fib_rule *,
					     struct sk_buff *,
					     struct fib_rule_hdr *,
					     struct nlattr **);
	int			(*delete)(struct fib_rule *);
	int			(*compare)(struct fib_rule *,
					   struct fib_rule_hdr *,
					   struct nlattr **);
	int			(*fill)(struct fib_rule *, struct sk_buff *,
					struct fib_rule_hdr *);
	size_t			(*nlmsg_payload)(struct fib_rule *);

	/* Called after modifications to the rules set, must flush
	 * the route cache if one exists. */
	void			(*flush_cache)(struct fib_rules_ops *ops);

	int			nlgroup;
	const struct nla_policy	*policy;
	struct list_head	rules_list;
	struct module		*owner;
	struct net		*fro_net;
	struct rcu_head		rcu;
};

#define FRA_GENERIC_POLICY \
	[FRA_IIFNAME]	= { .type = NLA_STRING, .len = IFNAMSIZ - 1 }, \
	[FRA_OIFNAME]	= { .type = NLA_STRING, .len = IFNAMSIZ - 1 }, \
	[FRA_PRIORITY]	= { .type = NLA_U32 }, \
	[FRA_FWMARK]	= { .type = NLA_U32 }, \
	[FRA_FWMASK]	= { .type = NLA_U32 }, \
	[FRA_TABLE]     = { .type = NLA_U32 }, \
	[FRA_SUPPRESS_PREFIXLEN] = { .type = NLA_U32 }, \
	[FRA_SUPPRESS_IFGROUP] = { .type = NLA_U32 }, \
	[FRA_GOTO]	= { .type = NLA_U32 }, \
	[FRA_L3MDEV]	= { .type = NLA_U8 }

static inline void fib_rule_get(struct fib_rule *rule)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/fib_rules.h: line 103 \n"); 
	atomic_inc(&rule->refcnt);
}

static inline void fib_rule_put(struct fib_rule *rule)
{
	if (atomic_dec_and_test(&rule->refcnt))
		kfree_rcu(rule, rcu);
}

#ifdef CONFIG_NET_L3_MASTER_DEV
static inline u32 fib_rule_get_table(struct fib_rule *rule,
				     struct fib_lookup_arg *arg)
{
	return rule->l3mdev ? arg->table : rule->table;
}
#else
static inline u32 fib_rule_get_table(struct fib_rule *rule,
				     struct fib_lookup_arg *arg)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/fib_rules.h: line 123 \n"); 
	return rule->table;
}
#endif

static inline u32 frh_get_table(struct fib_rule_hdr *frh, struct nlattr **nla)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/net/fib_rules.h: line 130 \n"); 
	if (nla[FRA_TABLE])
		return nla_get_u32(nla[FRA_TABLE]);
	return frh->table;
}

struct fib_rules_ops *fib_rules_register(const struct fib_rules_ops *,
					 struct net *);
void fib_rules_unregister(struct fib_rules_ops *);

int fib_rules_lookup(struct fib_rules_ops *, struct flowi *, int flags,
		     struct fib_lookup_arg *);
int fib_default_rule_add(struct fib_rules_ops *, u32 pref, u32 table,
			 u32 flags);

int fib_nl_newrule(struct sk_buff *skb, struct nlmsghdr *nlh);
int fib_nl_delrule(struct sk_buff *skb, struct nlmsghdr *nlh);
#endif
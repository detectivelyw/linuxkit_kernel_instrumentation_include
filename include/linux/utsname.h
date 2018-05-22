extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_UTSNAME_H
#define _LINUX_UTSNAME_H


#include <linux/sched.h>
#include <linux/kref.h>
#include <linux/nsproxy.h>
#include <linux/ns_common.h>
#include <linux/err.h>
#include <uapi/linux/utsname.h>

enum uts_proc {
	UTS_PROC_OSTYPE,
	UTS_PROC_OSRELEASE,
	UTS_PROC_VERSION,
	UTS_PROC_HOSTNAME,
	UTS_PROC_DOMAINNAME,
};

struct user_namespace;
extern struct user_namespace init_user_ns;

struct uts_namespace {
	struct kref kref;
	struct new_utsname name;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct ns_common ns;
};
extern struct uts_namespace init_uts_ns;

#ifdef CONFIG_UTS_NS
static inline void get_uts_ns(struct uts_namespace *ns)
{
	kref_get(&ns->kref);
}

extern struct uts_namespace *copy_utsname(unsigned long flags,
	struct user_namespace *user_ns, struct uts_namespace *old_ns);
extern void free_uts_ns(struct kref *kref);

static inline void put_uts_ns(struct uts_namespace *ns)
{
	kref_put(&ns->kref, free_uts_ns);
}
#else
static inline void get_uts_ns(struct uts_namespace *ns)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/utsname.h: line 53 \n"); 
}

static inline void put_uts_ns(struct uts_namespace *ns)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/utsname.h: line 58 \n"); 
}

static inline struct uts_namespace *copy_utsname(unsigned long flags,
	struct user_namespace *user_ns, struct uts_namespace *old_ns)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/utsname.h: line 64 \n"); 
	if (flags & CLONE_NEWUTS)
		return ERR_PTR(-EINVAL);

	return old_ns;
}
#endif

#ifdef CONFIG_PROC_SYSCTL
extern void uts_proc_notify(enum uts_proc proc);
#else
static inline void uts_proc_notify(enum uts_proc proc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/utsname.h: line 77 \n"); 
}
#endif

static inline struct new_utsname *utsname(void)
{
	return &current->nsproxy->uts_ns->name;
}

static inline struct new_utsname *init_utsname(void)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/utsname.h: line 88 \n"); 
	return &init_uts_ns.name;
}

extern struct rw_semaphore uts_sem;

#endif /* _LINUX_UTSNAME_H */

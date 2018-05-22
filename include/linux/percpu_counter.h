extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_PERCPU_COUNTER_H
#define _LINUX_PERCPU_COUNTER_H
/*
 * A simple "approximate counter" for use in ext2 and ext3 superblocks.
 *
 * WARNING: these things are HUGE.  4 kbytes per counter on 32-way P4.
 */

#include <linux/spinlock.h>
#include <linux/smp.h>
#include <linux/list.h>
#include <linux/threads.h>
#include <linux/percpu.h>
#include <linux/types.h>
#include <linux/gfp.h>

#ifdef CONFIG_SMP

struct percpu_counter {
	raw_spinlock_t lock;
	s64 count;
#ifdef CONFIG_HOTPLUG_CPU
	struct list_head list;	/* All percpu_counters are on a list */
#endif
	s32 __percpu *counters;
};

extern int percpu_counter_batch;

int __percpu_counter_init(struct percpu_counter *fbc, s64 amount, gfp_t gfp,
			  struct lock_class_key *key);

#define percpu_counter_init(fbc, value, gfp)				\
	({								\
		static struct lock_class_key __key;			\
									\
		__percpu_counter_init(fbc, value, gfp, &__key);		\
	})

void percpu_counter_destroy(struct percpu_counter *fbc);
void percpu_counter_set(struct percpu_counter *fbc, s64 amount);
void __percpu_counter_add(struct percpu_counter *fbc, s64 amount, s32 batch);
s64 __percpu_counter_sum(struct percpu_counter *fbc);
int __percpu_counter_compare(struct percpu_counter *fbc, s64 rhs, s32 batch);

static inline int percpu_counter_compare(struct percpu_counter *fbc, s64 rhs)
{
	return __percpu_counter_compare(fbc, rhs, percpu_counter_batch);
}

static inline void percpu_counter_add(struct percpu_counter *fbc, s64 amount)
{
	__percpu_counter_add(fbc, amount, percpu_counter_batch);
}

static inline s64 percpu_counter_sum_positive(struct percpu_counter *fbc)
{
	s64 ret = __percpu_counter_sum(fbc);
	return ret < 0 ? 0 : ret;
}

static inline s64 percpu_counter_sum(struct percpu_counter *fbc)
{
	return __percpu_counter_sum(fbc);
}

static inline s64 percpu_counter_read(struct percpu_counter *fbc)
{
	return fbc->count;
}

/*
 * It is possible for the percpu_counter_read() to return a small negative
 * number for some counter which should never be negative.
 *
 */
static inline s64 percpu_counter_read_positive(struct percpu_counter *fbc)
{
	s64 ret = fbc->count;

	barrier();		/* Prevent reloads of fbc->count */
	if (ret >= 0)
		return ret;
	return 0;
}

static inline int percpu_counter_initialized(struct percpu_counter *fbc)
{
	return (fbc->counters != NULL);
}

#else /* !CONFIG_SMP */

struct percpu_counter {
	s64 count;
};

static inline int percpu_counter_init(struct percpu_counter *fbc, s64 amount,
				      gfp_t gfp)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 105 \n"); 
	fbc->count = amount;
	return 0;
}

static inline void percpu_counter_destroy(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 112 \n"); 
}

static inline void percpu_counter_set(struct percpu_counter *fbc, s64 amount)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 117 \n"); 
	fbc->count = amount;
}

static inline int percpu_counter_compare(struct percpu_counter *fbc, s64 rhs)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 123 \n"); 
	if (fbc->count > rhs)
		return 1;
	else if (fbc->count < rhs)
		return -1;
	else
		return 0;
}

static inline int
__percpu_counter_compare(struct percpu_counter *fbc, s64 rhs, s32 batch)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 135 \n"); 
	return percpu_counter_compare(fbc, rhs);
}

static inline void
percpu_counter_add(struct percpu_counter *fbc, s64 amount)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 142 \n"); 
	preempt_disable();
	fbc->count += amount;
	preempt_enable();
}

static inline void
__percpu_counter_add(struct percpu_counter *fbc, s64 amount, s32 batch)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 151 \n"); 
	percpu_counter_add(fbc, amount);
}

static inline s64 percpu_counter_read(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 157 \n"); 
	return fbc->count;
}

/*
 * percpu_counter is intended to track positive numbers. In the UP case the
 * number should never be negative.
 */
static inline s64 percpu_counter_read_positive(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 167 \n"); 
	return fbc->count;
}

static inline s64 percpu_counter_sum_positive(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 173 \n"); 
	return percpu_counter_read_positive(fbc);
}

static inline s64 percpu_counter_sum(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 179 \n"); 
	return percpu_counter_read(fbc);
}

static inline int percpu_counter_initialized(struct percpu_counter *fbc)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 185 \n"); 
	return 1;
}

#endif	/* CONFIG_SMP */

static inline void percpu_counter_inc(struct percpu_counter *fbc)
{
	percpu_counter_add(fbc, 1);
}

static inline void percpu_counter_dec(struct percpu_counter *fbc)
{
	percpu_counter_add(fbc, -1);
}

static inline void percpu_counter_sub(struct percpu_counter *fbc, s64 amount)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/percpu_counter.h: line 203 \n"); 
	percpu_counter_add(fbc, -amount);
}

#endif /* _LINUX_PERCPU_COUNTER_H */

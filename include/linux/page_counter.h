extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_PAGE_COUNTER_H
#define _LINUX_PAGE_COUNTER_H

#include <linux/atomic.h>
#include <linux/kernel.h>
#include <asm/page.h>

struct page_counter {
	atomic_long_t count;
	unsigned long limit;
	struct page_counter *parent;

	/* legacy */
	unsigned long watermark;
	unsigned long failcnt;
};

#if BITS_PER_LONG == 32
#define PAGE_COUNTER_MAX LONG_MAX
#else
#define PAGE_COUNTER_MAX (LONG_MAX / PAGE_SIZE)
#endif

static inline void page_counter_init(struct page_counter *counter,
				     struct page_counter *parent)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/page_counter.h: line 31 \n"); 
	atomic_long_set(&counter->count, 0);
	counter->limit = PAGE_COUNTER_MAX;
	counter->parent = parent;
}

static inline unsigned long page_counter_read(struct page_counter *counter)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/page_counter.h: line 39 \n"); 
	return atomic_long_read(&counter->count);
}

void page_counter_cancel(struct page_counter *counter, unsigned long nr_pages);
void page_counter_charge(struct page_counter *counter, unsigned long nr_pages);
bool page_counter_try_charge(struct page_counter *counter,
			     unsigned long nr_pages,
			     struct page_counter **fail);
void page_counter_uncharge(struct page_counter *counter, unsigned long nr_pages);
int page_counter_limit(struct page_counter *counter, unsigned long limit);
int page_counter_memparse(const char *buf, const char *max,
			  unsigned long *nr_pages);

static inline void page_counter_reset_watermark(struct page_counter *counter)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/page_counter.h: line 55 \n"); 
	counter->watermark = page_counter_read(counter);
}

#endif /* _LINUX_PAGE_COUNTER_H */

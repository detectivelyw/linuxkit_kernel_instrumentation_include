extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _SCHED_DEADLINE_H
#define _SCHED_DEADLINE_H

/*
 * SCHED_DEADLINE tasks has negative priorities, reflecting
 * the fact that any of them has higher prio than RT and
 * NORMAL/BATCH tasks.
 */

#define MAX_DL_PRIO		0

static inline int dl_prio(int prio)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/deadline.h: line 18 \n"); 
	if (unlikely(prio < MAX_DL_PRIO))
		return 1;
	return 0;
}

static inline int dl_task(struct task_struct *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/deadline.h: line 26 \n"); 
	return dl_prio(p->prio);
}

static inline bool dl_time_before(u64 a, u64 b)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/deadline.h: line 32 \n"); 
	return (s64)(a - b) < 0;
}

#endif /* _SCHED_DEADLINE_H */

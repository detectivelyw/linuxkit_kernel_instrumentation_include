extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _SCHED_RT_H
#define _SCHED_RT_H

#include <linux/sched/prio.h>

static inline int rt_prio(int prio)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 12 \n"); 
	if (unlikely(prio < MAX_RT_PRIO))
		return 1;
	return 0;
}

static inline int rt_task(struct task_struct *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 20 \n"); 
	return rt_prio(p->prio);
}

#ifdef CONFIG_RT_MUTEXES
extern int rt_mutex_getprio(struct task_struct *p);
extern void rt_mutex_setprio(struct task_struct *p, int prio);
extern int rt_mutex_get_effective_prio(struct task_struct *task, int newprio);
extern struct task_struct *rt_mutex_get_top_task(struct task_struct *task);
extern void rt_mutex_adjust_pi(struct task_struct *p);
static inline bool tsk_is_pi_blocked(struct task_struct *tsk)
{
	return tsk->pi_blocked_on != NULL;
}
#else
static inline int rt_mutex_getprio(struct task_struct *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 37 \n"); 
	return p->normal_prio;
}

static inline int rt_mutex_get_effective_prio(struct task_struct *task,
					      int newprio)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 44 \n"); 
	return newprio;
}

static inline struct task_struct *rt_mutex_get_top_task(struct task_struct *task)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 50 \n"); 
	return NULL;
}
# define rt_mutex_adjust_pi(p)		do { } while (0)
static inline bool tsk_is_pi_blocked(struct task_struct *tsk)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/sched/rt.h: line 56 \n"); 
	return false;
}
#endif

extern void normalize_rt_tasks(void);


/*
 * default timeslice is 100 msecs (used only for SCHED_RR tasks).
 * Timeslices get refilled after they expire.
 */
#define RR_TIMESLICE		(100 * HZ / 1000)

#endif /* _SCHED_RT_H */

extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_PROFILE_H
#define _LINUX_PROFILE_H

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cpumask.h>
#include <linux/cache.h>

#include <asm/errno.h>

#define CPU_PROFILING	1
#define SCHED_PROFILING	2
#define SLEEP_PROFILING	3
#define KVM_PROFILING	4

struct proc_dir_entry;
struct pt_regs;
struct notifier_block;

#if defined(CONFIG_PROFILING) && defined(CONFIG_PROC_FS)
void create_prof_cpu_mask(void);
int create_proc_profile(void);
#else
static inline void create_prof_cpu_mask(void)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 30 \n"); 
}

static inline int create_proc_profile(void)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 35 \n"); 
	return 0;
}
#endif

enum profile_type {
	PROFILE_TASK_EXIT,
	PROFILE_MUNMAP
};

#ifdef CONFIG_PROFILING

extern int prof_on __read_mostly;

/* init basic kernel profiler */
int profile_init(void);
int profile_setup(char *str);
void profile_tick(int type);
int setup_profiling_timer(unsigned int multiplier);

/*
 * Add multiple profiler hits to a given address:
 */
void profile_hits(int type, void *ip, unsigned int nr_hits);

/*
 * Single profiler hit:
 */
static inline void profile_hit(int type, void *ip)
{
	/*
	 * Speedup for the common (no profiling enabled) case:
	 */
	if (unlikely(prof_on == type))
		profile_hits(type, ip, 1);
}

struct task_struct;
struct mm_struct;

/* task is in do_exit() */
void profile_task_exit(struct task_struct * task);

/* task is dead, free task struct ? Returns 1 if
 * the task was taken, 0 if the task should be freed.
 */
int profile_handoff_task(struct task_struct * task);

/* sys_munmap */
void profile_munmap(unsigned long addr);

int task_handoff_register(struct notifier_block * n);
int task_handoff_unregister(struct notifier_block * n);

int profile_event_register(enum profile_type, struct notifier_block * n);
int profile_event_unregister(enum profile_type, struct notifier_block * n);

struct pt_regs;

#else

#define prof_on 0

static inline int profile_init(void)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 100 \n"); 
	return 0;
}

static inline void profile_tick(int type)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 106 \n"); 
	return;
}

static inline void profile_hits(int type, void *ip, unsigned int nr_hits)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 112 \n"); 
	return;
}

static inline void profile_hit(int type, void *ip)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 118 \n"); 
	return;
}

static inline int task_handoff_register(struct notifier_block * n)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 124 \n"); 
	return -ENOSYS;
}

static inline int task_handoff_unregister(struct notifier_block * n)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 130 \n"); 
	return -ENOSYS;
}

static inline int profile_event_register(enum profile_type t, struct notifier_block * n)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 136 \n"); 
	return -ENOSYS;
}

static inline int profile_event_unregister(enum profile_type t, struct notifier_block * n)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/profile.h: line 142 \n"); 
	return -ENOSYS;
}

#define profile_task_exit(a) do { } while (0)
#define profile_handoff_task(a) (0)
#define profile_munmap(a) do { } while (0)

#endif /* CONFIG_PROFILING */

#endif /* _LINUX_PROFILE_H */

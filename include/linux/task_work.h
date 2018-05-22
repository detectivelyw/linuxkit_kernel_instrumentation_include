extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_TASK_WORK_H
#define _LINUX_TASK_WORK_H

#include <linux/list.h>
#include <linux/sched.h>

typedef void (*task_work_func_t)(struct callback_head *);

static inline void
init_task_work(struct callback_head *twork, task_work_func_t func)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_work.h: line 16 \n"); 
	twork->func = func;
}

int task_work_add(struct task_struct *task, struct callback_head *twork, bool);
struct callback_head *task_work_cancel(struct task_struct *, task_work_func_t);
void task_work_run(void);

static inline void exit_task_work(struct task_struct *task)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_work.h: line 26 \n"); 
	task_work_run();
}

#endif	/* _LINUX_TASK_WORK_H */

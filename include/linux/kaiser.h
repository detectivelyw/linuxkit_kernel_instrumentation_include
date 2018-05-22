extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_KAISER_H
#define _LINUX_KAISER_H

#ifdef CONFIG_PAGE_TABLE_ISOLATION
#include <asm/kaiser.h>

static inline int kaiser_map_thread_stack(void *stack)
{
	/*
	 * Map that page of kernel stack on which we enter from user context.
	 */
	return kaiser_add_mapping((unsigned long)stack +
			THREAD_SIZE - PAGE_SIZE, PAGE_SIZE, __PAGE_KERNEL);
}

static inline void kaiser_unmap_thread_stack(void *stack)
{
	/*
	 * Note: may be called even when kaiser_map_thread_stack() failed.
	 */
	kaiser_remove_mapping((unsigned long)stack +
			THREAD_SIZE - PAGE_SIZE, PAGE_SIZE);
}
#else

/*
 * These stubs are used whenever CONFIG_PAGE_TABLE_ISOLATION is off, which
 * includes architectures that support KAISER, but have it disabled.
 */

static inline void kaiser_init(void)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kaiser.h: line 37 \n"); 
}
static inline int kaiser_add_mapping(unsigned long addr,
				     unsigned long size, u64 flags)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kaiser.h: line 42 \n"); 
	return 0;
}
static inline void kaiser_remove_mapping(unsigned long start,
					 unsigned long size)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kaiser.h: line 48 \n"); 
}
static inline int kaiser_map_thread_stack(void *stack)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kaiser.h: line 52 \n"); 
	return 0;
}
static inline void kaiser_unmap_thread_stack(void *stack)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kaiser.h: line 57 \n"); 
}

#endif /* !CONFIG_PAGE_TABLE_ISOLATION */
#endif /* _LINUX_KAISER_H */

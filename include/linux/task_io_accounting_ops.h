extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
/*
 * Task I/O accounting operations
 */
#ifndef __TASK_IO_ACCOUNTING_OPS_INCLUDED
#define __TASK_IO_ACCOUNTING_OPS_INCLUDED

#include <linux/sched.h>

#ifdef CONFIG_TASK_IO_ACCOUNTING
static inline void task_io_account_read(size_t bytes)
{
	current->ioac.read_bytes += bytes;
}

/*
 * We approximate number of blocks, because we account bytes only.
 * A 'block' is 512 bytes
 */
static inline unsigned long task_io_get_inblock(const struct task_struct *p)
{
	return p->ioac.read_bytes >> 9;
}

static inline void task_io_account_write(size_t bytes)
{
	current->ioac.write_bytes += bytes;
}

/*
 * We approximate number of blocks, because we account bytes only.
 * A 'block' is 512 bytes
 */
static inline unsigned long task_io_get_oublock(const struct task_struct *p)
{
	return p->ioac.write_bytes >> 9;
}

static inline void task_io_account_cancelled_write(size_t bytes)
{
	current->ioac.cancelled_write_bytes += bytes;
}

static inline void task_io_accounting_init(struct task_io_accounting *ioac)
{
	memset(ioac, 0, sizeof(*ioac));
}

static inline void task_blk_io_accounting_add(struct task_io_accounting *dst,
						struct task_io_accounting *src)
{
	dst->read_bytes += src->read_bytes;
	dst->write_bytes += src->write_bytes;
	dst->cancelled_write_bytes += src->cancelled_write_bytes;
}

#else

static inline void task_io_account_read(size_t bytes)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 64 \n"); 
}

static inline unsigned long task_io_get_inblock(const struct task_struct *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 69 \n"); 
	return 0;
}

static inline void task_io_account_write(size_t bytes)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 75 \n"); 
}

static inline unsigned long task_io_get_oublock(const struct task_struct *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 80 \n"); 
	return 0;
}

static inline void task_io_account_cancelled_write(size_t bytes)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 86 \n"); 
}

static inline void task_io_accounting_init(struct task_io_accounting *ioac)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 91 \n"); 
}

static inline void task_blk_io_accounting_add(struct task_io_accounting *dst,
						struct task_io_accounting *src)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 97 \n"); 
}

#endif /* CONFIG_TASK_IO_ACCOUNTING */

#ifdef CONFIG_TASK_XACCT
static inline void task_chr_io_accounting_add(struct task_io_accounting *dst,
						struct task_io_accounting *src)
{
	dst->rchar += src->rchar;
	dst->wchar += src->wchar;
	dst->syscr += src->syscr;
	dst->syscw += src->syscw;
}
#else
static inline void task_chr_io_accounting_add(struct task_io_accounting *dst,
						struct task_io_accounting *src)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/task_io_accounting_ops.h: line 115 \n"); 
}
#endif /* CONFIG_TASK_XACCT */

static inline void task_io_accounting_add(struct task_io_accounting *dst,
						struct task_io_accounting *src)
{
	task_chr_io_accounting_add(dst, src);
	task_blk_io_accounting_add(dst, src);
}
#endif /* __TASK_IO_ACCOUNTING_OPS_INCLUDED */

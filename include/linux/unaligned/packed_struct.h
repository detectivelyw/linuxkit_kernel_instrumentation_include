extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_UNALIGNED_PACKED_STRUCT_H
#define _LINUX_UNALIGNED_PACKED_STRUCT_H

#include <linux/kernel.h>

struct __una_u16 { u16 x; } __packed;
struct __una_u32 { u32 x; } __packed;
struct __una_u64 { u64 x; } __packed;

static inline u16 __get_unaligned_cpu16(const void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 16 \n"); 
	const struct __una_u16 *ptr = (const struct __una_u16 *)p;
	return ptr->x;
}

static inline u32 __get_unaligned_cpu32(const void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 23 \n"); 
	const struct __una_u32 *ptr = (const struct __una_u32 *)p;
	return ptr->x;
}

static inline u64 __get_unaligned_cpu64(const void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 30 \n"); 
	const struct __una_u64 *ptr = (const struct __una_u64 *)p;
	return ptr->x;
}

static inline void __put_unaligned_cpu16(u16 val, void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 37 \n"); 
	struct __una_u16 *ptr = (struct __una_u16 *)p;
	ptr->x = val;
}

static inline void __put_unaligned_cpu32(u32 val, void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 44 \n"); 
	struct __una_u32 *ptr = (struct __una_u32 *)p;
	ptr->x = val;
}

static inline void __put_unaligned_cpu64(u64 val, void *p)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/unaligned/packed_struct.h: line 51 \n"); 
	struct __una_u64 *ptr = (struct __una_u64 *)p;
	ptr->x = val;
}

#endif /* _LINUX_UNALIGNED_PACKED_STRUCT_H */

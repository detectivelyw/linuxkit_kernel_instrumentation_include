extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _LINUX_KDEV_T_H
#define _LINUX_KDEV_T_H

#include <uapi/linux/kdev_t.h>

#define MINORBITS	20
#define MINORMASK	((1U << MINORBITS) - 1)

#define MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)	((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))

#define print_dev_t(buffer, dev)					\
	sprintf((buffer), "%u:%u\n", MAJOR(dev), MINOR(dev))

#define format_dev_t(buffer, dev)					\
	({								\
		sprintf(buffer, "%u:%u", MAJOR(dev), MINOR(dev));	\
		buffer;							\
	})

/* acceptable for old filesystems */
static inline bool old_valid_dev(dev_t dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 29 \n"); 
	return MAJOR(dev) < 256 && MINOR(dev) < 256;
}

static inline u16 old_encode_dev(dev_t dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 35 \n"); 
	return (MAJOR(dev) << 8) | MINOR(dev);
}

static inline dev_t old_decode_dev(u16 val)
{
	return MKDEV((val >> 8) & 255, val & 255);
}

static inline u32 new_encode_dev(dev_t dev)
{
	unsigned major = MAJOR(dev);
	unsigned minor = MINOR(dev);
	return (minor & 0xff) | (major << 8) | ((minor & ~0xff) << 12);
}

static inline dev_t new_decode_dev(u32 dev)
{
	unsigned major = (dev & 0xfff00) >> 8;
	unsigned minor = (dev & 0xff) | ((dev >> 12) & 0xfff00);
	return MKDEV(major, minor);
}

static inline u64 huge_encode_dev(dev_t dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 60 \n"); 
	return new_encode_dev(dev);
}

static inline dev_t huge_decode_dev(u64 dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 66 \n"); 
	return new_decode_dev(dev);
}

static inline int sysv_valid_dev(dev_t dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 72 \n"); 
	return MAJOR(dev) < (1<<14) && MINOR(dev) < (1<<18);
}

static inline u32 sysv_encode_dev(dev_t dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 78 \n"); 
	return MINOR(dev) | (MAJOR(dev) << 18);
}

static inline unsigned sysv_major(u32 dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 84 \n"); 
	return (dev >> 18) & 0x3fff;
}

static inline unsigned sysv_minor(u32 dev)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/kdev_t.h: line 90 \n"); 
	return dev & 0x3ffff;
}

#endif

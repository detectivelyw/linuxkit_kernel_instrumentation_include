extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
/**
 * lib/minmax.c: windowed min/max tracker by Kathleen Nichols.
 *
 */
#ifndef MINMAX_H
#define MINMAX_H

#include <linux/types.h>

/* A single data point for our parameterized min-max tracker */
struct minmax_sample {
	u32	t;	/* time measurement was taken */
	u32	v;	/* value measured */
};

/* State for the parameterized min-max tracker */
struct minmax {
	struct minmax_sample s[3];
};

static inline u32 minmax_get(const struct minmax *m)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/win_minmax.h: line 27 \n"); 
	return m->s[0].v;
}

static inline u32 minmax_reset(struct minmax *m, u32 t, u32 meas)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/win_minmax.h: line 33 \n"); 
	struct minmax_sample val = { .t = t, .v = meas };

	m->s[2] = m->s[1] = m->s[0] = val;
	return m->s[0].v;
}

u32 minmax_running_max(struct minmax *m, u32 win, u32 t, u32 meas);
u32 minmax_running_min(struct minmax *m, u32 win, u32 t, u32 meas);

#endif

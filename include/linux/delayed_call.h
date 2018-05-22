extern int kernel_init_done; 
#include <linux/linkage.h> 
asmlinkage __printf(1, 2) __cold 
int printk(const char *fmt, ...); 
#ifndef _DELAYED_CALL_H
#define _DELAYED_CALL_H

/*
 * Poor man's closures; I wish we could've done them sanely polymorphic,
 * but...
 */

struct delayed_call {
	void (*fn)(void *);
	void *arg;
};

#define DEFINE_DELAYED_CALL(name) struct delayed_call name = {NULL, NULL}

/* I really wish we had closures with sane typechecking... */
static inline void set_delayed_call(struct delayed_call *call,
		void (*fn)(void *), void *arg)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/delayed_call.h: line 24 \n"); 
	call->fn = fn;
	call->arg = arg;
}

static inline void do_delayed_call(struct delayed_call *call)
{
	if (call->fn)
		call->fn(call->arg);
}

static inline void clear_delayed_call(struct delayed_call *call)
{
	if (kernel_init_done == 1) printk("We reached unpopular paths in include/linux/delayed_call.h: line 37 \n"); 
	call->fn = NULL;
}
#endif

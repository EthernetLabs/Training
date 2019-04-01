#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#define _QUEUE_NAME "KERN_MOD_QUEUE"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux driver.");
MODULE_VERSION("0.1");


extern int printk(const char *fmt, ...); //printk header: asmlinkage __visible int printk(const char *fmt, ...)
typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

//static void _call_printk(void *);
static void _call_printk(struct work_struct *);

//Task and schedule
static struct workqueue_struct *__queue;
//static struct work_struct Task;
static struct delayed_work Task;
//DECLARE_WORK(Task, _call_printk);
static DECLARE_DELAYED_WORK(Task, _call_printk);

//static void _call_printk(const char *__mesg)
static void _call_printk(struct work_struct *work)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ INIT\n");
	queue_delayed_work(__queue, &Task, 100);
}


static int _init_module(void)
{
    //__fptr __fptr_ptr;
    //__fptr_ptr.callfunc = printk;
	//__fptr_ptr.callfunc(KERN_ALERT "Hi Weqaar\n");
	//_call_printk("Hi Weqaar\n");
	__queue = create_workqueue(_QUEUE_NAME);
	queue_delayed_work(__queue, &Task, 100);
    return 0;
}

static void _cleanup_module(void)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");
	flush_workqueue(__queue);
	destroy_workqueue(__queue);
}

module_init(_init_module);
module_exit(_cleanup_module);

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux driver - 0.");
MODULE_VERSION("0.1");


extern int printk(const char *fmt, ...); //printk header: asmlinkage __visible int printk(const char *fmt, ...)
typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;


static int _init_module(void)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "Hi Weqaar\n");
    return 0;
}

static void _cleanup_module(void)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");
}

module_init(_init_module);
module_exit(_cleanup_module);

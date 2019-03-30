#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux driver.");
MODULE_VERSION("0.1");

static int _init_module(void)
{
    printk(KERN_ALERT "Hi Weqaar\n");
    return 0;
}

static void _cleanup_module(void)
{
    printk(KERN_ALERT "Exiting, Bye Weqaar\n");
}

module_init(_init_module);
module_exit(_cleanup_module);

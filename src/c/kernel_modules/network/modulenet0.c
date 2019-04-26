#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
//Special files
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ethtool.h>
#include "modulenet0.h"

#define _QUEUE_NAME "KERN_MOD_QUEUE"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux network driver 0");
MODULE_VERSION("0.3");


extern int printk(const char *fmt, ...); //printk header: asmlinkage __visible int printk(const char *fmt, ...)
typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

//Ethernet
static const struct net_device_ops modulenet_netdev_ops = {
	.ndo_init			 = modulenet_init,
	.ndo_open            = modulenet_open,
	.ndo_stop            = modulenet_release,
	.ndo_start_xmit      = modulenet_tx,
	.ndo_do_ioctl        = modulenet_ioctl,
	.ndo_set_config      = modulenet_config,
	.ndo_get_stats       = modulenet_stats,
	.ndo_change_mtu      = modulenet_change_mtu,
	.ndo_tx_timeout      = modulenet_tx_timeout,
	.ndo_set_mac_address = modulenet_set_mac_addr,
	.ndo_validate_addr	 = modulenet_validate_addr
	
};

static void _call_printk(struct work_struct *);

//Task and schedule
static struct workqueue_struct *__queue;
static struct delayed_work Task;
static DECLARE_DELAYED_WORK(Task, _call_printk);

static void _call_printk(struct work_struct *work)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ INIT\n");
	queue_delayed_work(__queue, &Task, 100);
}




static int _init_module(void)
{
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

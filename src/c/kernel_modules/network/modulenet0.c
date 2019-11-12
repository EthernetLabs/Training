/*
modulenet kernel driver - NIC
Author: Weqaar Janjua

Features:
* Registers /proc entry as /proc/modulenet
* Implements Interrupt driven and NAPI driven functionality


*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
//network related
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ethtool.h>
#include <net/ip.h>
//proc related
#include <linux/proc_fs.h>
#include "modulenet0.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux network driver 0");
MODULE_VERSION("0.4");

extern int printk(const char *fmt, ...); //printk header: asmlinkage __visible int printk(const char *fmt, ...)
typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

struct proc_dir_entry modulenet_proc_entry = {
  0,                     /* low_ino - inode number (0 for dynamic)  */
  9,                    /* namelen - length of entry name          */
  "modulenet",        /* name                                    */
  S_IFREG | S_IRUGO,     /* mode                                    */
  1,                     /* nlinks                                  */
  0,                     /* uid - owner                             */
  0,                     /* gid - group                             */
  0,                     /* size - not used                         */
  NULL,                  /* ops - inode operations (use default)    */
  &show_modulenet_stats  /* read_proc - address of read function    */
};

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

static void _call_printk(struct work_struct *work)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ INIT\n");
}

/*set MAC
struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

int dev_set_mac_address (	struct net_device * dev,
 	struct sockaddr * sa);

*/

static int _init_module(void)
{

    modulenet_interrupt = use_napi ? modulenet_napi_interrupt : modulenet_regular_interrupt;

	int err = proc_register(&proc_root,&modulenet_proc_entry);
  	if (!err)
    	printk("<1> simple_entry: registered with inode %d.\n", modulenet_proc_entry.low_ino);
  	else
    	printk("<1> simple_entry: registration error, code %d.\n",err);
  	return err;

    return 0;
}

static void _cleanup_module(void)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");

	int err = proc_unregister(&proc_root,modulenet_proc_entry.low_ino);
  	if (!err)
    	printk("<1> simple_entry: unregistered inode %d.\n", modulenet_proc_entry.low_ino);
  	else
    	printk("<1> simple_entry: unregistration error, code %d.\n",err);

}

module_init(_init_module);
module_exit(_cleanup_module);

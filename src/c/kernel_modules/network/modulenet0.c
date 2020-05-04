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
//network
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <net/ip.h>
#include <linux/tcp.h>
//proc
#include <linux/proc_fs.h>
#include "modulenet0.h"
//pci
#include <linux/pci.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux network driver 0");
MODULE_VERSION("0.5");

//module parameters
static int lockup = 0;
module_param(lockup, int, 0);

static int timeout = ETH_TIMEOUT;
module_param(timeout, int, 0);

static int use_napi = 0;
module_param(use_napi, int, 0);


extern int printk(const char *fmt, ...); //printk header: asmlinkage __visible int printk(const char *fmt, ...)
typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;


struct eth_packet {
	struct eth_packet *next;
	struct net_device *dev;
	int	datalen;
	u8 data[ETH_DATA_LEN];
};

struct eth_priv {
	struct net_device_stats stats;
	int status;
	struct eth_packet *ppool;
	struct eth_packet *rx_queue;  /* List of incoming packets */
	int rx_int_enabled;
	int tx_packetlen;
	u8 *tx_packetdata;
	struct sk_buff *skb;
	spinlock_t lock;
	struct net_device *dev;
	struct napi_struct napi;
};

struct proc_dir_entry modulenet_proc_entry = {
  0,                     	/* low_ino - inode number (0 for dynamic)  */
  9,                    	/* namelen - length of entry name          */
  "modulenet",        		/* name                                    */
  S_IFREG | S_IRUGO,     	/* mode                                    */
  1,                     	/* nlinks                                  */
  0,                     	/* uid - owner                             */
  0,                     	/* gid - group                             */
  0,                    	/* size - not used                         */
  NULL,                  	/* ops - inode operations (use default)    */
  &show_modulenet_stats  	/* read_proc - address of read function    */
};

//Ethernet
static const struct net_device_ops modulenet_netdev_ops = {
	//.ndo_init			 = modulenet_init,
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
	//.ndo_bpf = modulenet_bpf, //https://elixir.bootlin.com/linux/latest/source/include/linux/netdevice.h#L1267
	//.nod_xdp_xmit = modulenet_xdp_xmit
	
};

static const struct header_ops modulenet_header_ops = {
   	.create  = eth_header,
	.rebuild = eth_rebuild_header
};

static const struct ethtool_ops *modulenet_ethtool_ops = {

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



void eth_init(struct net_device *dev)
{
	struct eth_priv *priv;
#if 0

#endif

	ether_setup(dev); /* assign some of the fields */
	//net_device fields
	dev->name = DEV_NAME;
	dev->watchdog_timeo = timeout;
	dev->netdev_ops = &modulenet_netdev_ops;
	dev->header_ops = &modulenet_header_ops;
	dev->irq = DEV_IRQ;
	/* keep the default flags, just add NOARP */
	dev->flags           |= IFF_NOARP;
	dev->features        |= NETIF_F_HW_CSUM;

	priv = netdev_priv(dev);
	if (use_napi) {
		netif_napi_add(dev, &priv->napi, snull_poll,2);
	}
	memset(priv, 0, sizeof(struct eth_priv));
	spin_lock_init(&priv->lock);
	snull_rx_ints(dev, 1);		/* enable receive interrupts */
	snull_setup_pool(dev);
}


//Kernel module specific functions

static int _init_module(void)
{

	int result, i, ret = -ENOMEM;

    modulenet_interrupt = use_napi ? modulenet_napi_interrupt : modulenet_regular_interrupt;

	//proc
	int ret = proc_register(&proc_root,&modulenet_proc_entry);
  	if (!ret)
    	printk("<1> simple_entry: registered with inode %d.\n", modulenet_proc_entry.low_ino);
  	else
	  	{
    		printk("<1> simple_entry: registration error, code %d.\n", ret);
  			return err;
		}

	//pci
	struct pci_dev *pcidev;
    pcidev = pci_find_device(NIC_VENDOR_ID, NIC_DEVICE_ID, NULL);
    if(!pcidev) {
        printk("<1>Device not found\n");
		return pcidev;
	}
    else
        printk("<1>Device found\n");

	/* Allocate the devices */
	eth_devs[0] = alloc_netdev(sizeof(struct eth_priv), DEV_NAME, eth_init);
	//eth_devs[0] = alloc_netdev(sizeof(struct eth_priv), "nic%d", eth_init);

	if (eth_devs[0] == NULL)
		goto out;

	ret = -ENODEV;
	for (i = 0; i < 1;  i++)
		if ((result = register_netdev(eth_devs[i])))
			printk("modulenet: error %i registering device \"%s\"\n", result, eth_devs[i]->name);
		else
			ret = 0;

   out:
		if (ret) 
			_cleanup_module();
		return ret;
}

static void _cleanup_module(void)
{
	int i;
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");

	//unregister proc
	int err = proc_unregister(&proc_root,modulenet_proc_entry.low_ino);
  	if (!err)
    	printk("<1> simple_entry: unregistered inode %d.\n", modulenet_proc_entry.low_ino);
  	else
    	printk("<1> simple_entry: unregistration error, code %d.\n",err);
    
	//unregister eth
	for (i = 0; i < 1;  i++) {
		if (eth_devs[i]) {
			unregister_netdev(eth_devs[i]);
			snull_teardown_pool(eth_devs[i]);
			free_netdev(eth_devs[i]);
		}
	}
	return;
}


}

module_init(_init_module);
module_exit(_cleanup_module);

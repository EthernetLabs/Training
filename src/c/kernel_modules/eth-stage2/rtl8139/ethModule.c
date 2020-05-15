/*
modulenet kernel driver - NIC
Stage 2
Author: Weqaar Janjua

Features:
* Registers /proc entry as /proc/modulenet
* Implements Interrupt driven and NAPI driven functionality
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
//proc
#include <linux/uaccess.h>
#include <linux/cred.h>
#include <linux/proc_fs.h>

//
#include <linux/sched.h>
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <asm/checksum.h>

#include "ethModule.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Stage-2 Ethernet Linux PCI NIC driver for rtl8139");
MODULE_VERSION("0.1.5");

//ETH
static const struct net_device_ops eth_netdev_ops = {
	.ndo_open            = eth_open,
	.ndo_stop            = eth_release,
	.ndo_start_xmit      = eth_tx,
	.ndo_do_ioctl        = eth_ioctl,
	.ndo_set_config      = eth_config,
	.ndo_get_stats       = eth_stats,
	.ndo_change_mtu      = eth_change_mtu,
	.ndo_tx_timeout      = eth_tx_timeout,
	.ndo_set_mac_address = eth_set_mac_addr,
	.ndo_validate_addr	 = eth_validate_addr
	//.ndo_bpf = modulenet_bpf, //https://elixir.bootlin.com/linux/latest/source/include/linux/netdevice.h#L1267
	//.nod_xdp_xmit = modulenet_xdp_xmi
};

int eth_open(struct net_device *eth_dev)
{
	return 0;
}

int eth_release(struct net_device *eth_dev)
{
    /* release ports, irq and such -- like fops->close */

	netif_stop_queue(eth_dev); /* can't transmit any more */
	return 0;
}

/*
 * Configuration changes (passed on by ifconfig)
 */
int eth_config(struct net_device *eth_dev, struct ifmap *map)
{
	if (eth_dev->flags & IFF_UP) /* can't act on a running interface */
		return -EBUSY;

	/* Don't allow changing the I/O address */
	if (map->base_addr != eth_dev->base_addr) {
		printk(KERN_WARNING "eth: Can't change I/O address\n");
		return -EOPNOTSUPP;
	}

	/* Allow changing the IRQ */
	if (map->irq != eth_dev->irq) {
		eth_dev->irq = map->irq;
        	/* request_irq() is delayed to open-time */
	}

	/* ignore other fields */
	return 0;
}

/*
 * Transmit a packet (low level interface)
 */
static void eth_hw_tx(char *buf, int len, struct net_device *eth_dev)
{

}

/*
 * Transmit a packet (called by the kernel)
 */
int eth_tx(struct sk_buff *skb, struct net_device *eth_dev)
{
	return 0; /* Our simple device can not fail */
}

/*
 * Deal with a transmit timeout.
 */
void eth_tx_timeout (struct net_device *eth_dev)
{
	return;
}

/*
 * Ioctl commands 
 */
int eth_ioctl(struct net_device *eth_dev, struct ifreq *rq, int cmd)
{
    printk(KERN_INFO "ioctl\n");
	return 0;
}

/*
 * Return statistics to the caller
 */
struct net_device_stats *eth_stats(struct net_device *eth_dev)
{
	struct eth_priv *priv = netdev_priv(eth_dev);
	return &priv->stats;
}

bool eth_validate_header(const char *ll_header, unsigned int len)
{
	return 0;
}

int	eth_set_mac_addr(struct net_device *eth_dev, void *addr) {

}

int	eth_validate_addr(struct net_device *eth_dev) {

}

//PROC
/**
 * This funtion is called when the /proc file is read
 */
static ssize_t procfs_read(struct file *filp, char *buffer,	size_t length, loff_t * offset)
{
	static int finished = 0;

	if ( finished ) {
		printk(KERN_INFO "procfs_read: END\n");
		finished = 0;
		return 0;
	}
	
	finished = 1;
		
	/* 
	 * We use put_to_user to copy the string from the kernel's
	 * memory segment to the memory segment of the process
	 * that called us. get_from_user, BTW, is
	 * used for the reverse. 
	 */
	if ( copy_to_user(buffer, procfs_buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}

	printk(KERN_INFO "procfs_read: read %lu bytes\n", procfs_buffer_size);

	return procfs_buffer_size;	/* Return the number of bytes "read" */
}

/*
 * This function is called when /proc is written
 */
static ssize_t
procfs_write(struct file *file, const char *buffer, size_t len, loff_t * off)
{
	if ( len > PROCFS_MAX_SIZE )	{
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	else	{
		procfs_buffer_size = len;
	}
	
	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size)) {
		return -EFAULT;
	}

	printk(KERN_INFO "procfs_write: write %lu bytes\n", procfs_buffer_size);
	
	return procfs_buffer_size;
}

/* 
 * This function decides whether to allow an operation
 * (return zero) or not allow it (return a non-zero
 * which indicates why it is not allowed).
 *
 * The operation can be one of the following values:
 * 0 - Execute (run the "file" - meaningless in our case)
 * 2 - Write (input to the kernel module)
 * 4 - Read (output from the kernel module)
 *
 * This is the real function that checks file
 * permissions. The permissions returned by ls -l are
 * for referece only, and can be overridden here.
 */

static int module_permission(struct inode *inode, int op)
{
	/* 
	 * We allow everybody to read from our module, but
	 * only root (uid 0) may write to it 
	 */
	//if (op == 4 || (op == 2 && current_euid() == 0))
	if (op == 4 || (op == 2 && (current->cred)->uid.val == 0))
		return 0;

	/* 
	 * If it's anything else, access is denied 
	 */
	return -EACCES;
}

/* 
 * The file is opened - we don't really care about
 * that, but it does mean we need to increment the
 * module's reference count. 
 */
int procfs_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}

/* 
 * The file is closed - again, interesting only because
 * of the reference count. 
 */
int procfs_close(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;		/* success */
}

static struct file_operations procFileOps = {
	.read 	 = procfs_read,
	.write 	 = procfs_write,
	.open 	 = procfs_open,
	.release = procfs_close,
};

//PRINTK
static void _call_printk(struct work_struct *work)
{
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ INIT\n");
}

//PCI
//enables PIC device
static int nic_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int ret;
	//struct net_device *netdev;

    printk(KERN_INFO "nic_probe: Device found [%x]:[%x]\n", pdev->vendor, pdev->device);
    printk(KERN_INFO "nic_probe: Device IRQ: %d\n", pdev->irq);
    
	printk(KERN_INFO "Enabling Device: [%x]:[%x]\n", pdev->vendor, pdev->device);
	ret = pci_enable_device(pdev);//dd book p.314
	if (ret) {
    	printk(KERN_INFO "ret: %d\n", ret);
		return ret;
	}

	pciDev = pdev;
	//memcpy(pciDev, pdev, sizeof(struct pci_dev));

	return ret;
}

static void nic_remove(struct pci_dev *pdev)
{
	pci_disable_device(pdev);
    printk(KERN_INFO "DEBUG>> NIC removed\n");
}

static int nic_resume(struct pci_dev *pdev)
{
    printk(KERN_INFO "DEBUG>> nic_resume\n");
	pci_disable_device(pdev);
}

static int nic_suspend(struct pci_dev *pdev, pm_message_t state)
{
    printk(KERN_INFO "DEBUG>> nic_suspend\n");
	pci_disable_device(pdev);
}

static void nic_shutdown(struct pci_dev *pdev)
{
    printk(KERN_INFO "DEBUG>> nic_shutdown\n");
	pci_disable_device(pdev);
}

//ETH
void eth_init(struct net_device *eth_dev)
{
	ether_setup(eth_dev); /* assign some of the fields */
	eth_dev->netdev_ops = &eth_netdev_ops;
	eth_dev->flags     	|= IFF_BROADCAST;
	eth_dev->features  	|= NETIF_F_HW_CSUM;

	printk(KERN_INFO "DEBUG>> eth_init\n");

	//This isn't necessary to register net_device
	priv = netdev_priv(eth_dev);
	memset(priv, 0, sizeof(struct eth_priv));

	return 0;
}


//Kernel module specific functions
static int _init_module(void)
{
	int i, result, ret = -ENOMEM;
	unsigned long mmio_start, mmio_end, mmio_len, mmio_flags;
    void *ioaddr;

	//proc
	pciModule_proc_entry = proc_create(ENTRY_NAME, S_IFREG | S_IRUGO| S_IWUSR, NULL, &procFileOps);
  	if (pciModule_proc_entry == NULL)
    	return ret;

	printk(KERN_INFO "/proc/%s created\n", ENTRY_NAME);
	
	printk(KERN_INFO "DEBUG>> init\n");
	//pci
	if (pci_dev_present(intel_rtl_nics_table)) {
        printk(KERN_INFO "Device present!\n");
	} else {
        printk(KERN_INFO "Error: device not present!\n");
    	return ret;
	}

	//https://elixir.bootlin.com/linux/v5.1/source/include/linux/pci.h#L770
	pciDriver.name = ENTRY_NAME;
	pciDriver.id_table = intel_rtl_nics_table;
	pciDriver.probe = nic_probe;
	pciDriver.remove = nic_remove;
	pciDriver.resume = nic_resume;
	pciDriver.suspend = nic_suspend;
	pciDriver.shutdown = nic_shutdown;

	//https://elixir.bootlin.com/linux/v5.1/source/drivers/pci/pci-driver.c#L1388
	pci_register_driver(&pciDriver); //returns driver_register(&drv->driver);

	/* Allocate the devices */
	//https://elixir.bootlin.com/linux/v5.1/source/include/uapi/linux/netdevice.h#L42
	eth_net_device = alloc_netdev(sizeof(struct eth_priv), DEV_NAME, NET_NAME_UNKNOWN, eth_init);

	ret = -ENODEV;
	
	if (eth_net_device == NULL) {
		printk(KERN_INFO "DEBUG>> eth_net_device is NULL\n");
		goto out;
	}

	priv->pciDev = pciDev;

	//
	 /* get PCI memory mapped I/O space base address from BAR1 */
	
	mmio_start = pci_resource_start(pciDev, 1);
	mmio_end = pci_resource_end(pciDev, 1);
	mmio_len = pci_resource_len(pciDev, 1);
	mmio_flags = pci_resource_flags(pciDev, 1);
	/*
	mmio_start = pci_resource_start(priv->pciDev, 1);
	mmio_end = pci_resource_end(priv->pciDev, 1);
	mmio_len = pci_resource_len(priv->pciDev, 1);
	mmio_flags = pci_resource_flags(priv->pciDev, 1);
	*/
	/* make sure above region is MMI/O */
	if(!(mmio_flags & IORESOURCE_MEM)) {
			printk(KERN_INFO "region not MMI/O region\n");
			goto out;
	}
	
	/* get PCI memory space */
	if(pci_request_regions(priv->pciDev, DRIVER_NAME)) {
			printk(KERN_INFO "Could not get PCI region\n");
			goto out;
	}

	pci_set_master(priv->pciDev);
	printk(KERN_INFO "DEBUG>> pci_set_master\n");

	/* ioremap MMI/O region */
	ioaddr = ioremap(mmio_start, mmio_len);
	if(!ioaddr) {
			printk(KERN_INFO "Could not ioremap\n");
			goto out;
	}

	eth_net_device->base_addr = (long)ioaddr;
	priv->mmio_addr = ioaddr;
	priv->regs_len = mmio_len;

	for(i = 0; i < 6; i++) {  /* Hardware Address */
		eth_net_device->dev_addr[i] = readb(eth_net_device->base_addr+i);
		eth_net_device->broadcast[i] = 0xff;
	}
	eth_net_device->hard_header_len = 14;

	//memcpy(eth_net_device->name, DRIVER_NAME, sizeof(DRIVER_NAME));

	/*
	eth_net_device->irq = pciDev->irq;
	eth_net_device->open = eth_open;
	eth_net_device->stop = eth_stop;
	eth_net_device->hard_start_xmit = eth_start_xmit;
	eth_net_device->get_stats = eth_get_stats;
	*/

	for (i = 0; i < 1;  i++)
		if ((result = register_netdev(eth_net_device)))
				printk("modulenet: error %i registering device \"%s\"\n", result, eth_net_device->name);
		else {
				printk("Device registered: %s\n", eth_net_device->name);
				ret = 0;
		}

   	out:
		if (ret) {
			printk("Error registering device \"%s\"\n", eth_net_device->name);
			return ret;
		}

	return ret;
}

static void _cleanup_module(void)
{
	int i;
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");

	//unregister proc
	proc_remove(pciModule_proc_entry);
	printk(KERN_INFO "DEBUG>> /proc/%s removed\n", ENTRY_NAME);
	//unregister net_device
	unregister_netdev(eth_net_device);
	printk(KERN_INFO "DEBUG>> device: %s unregistered\n", eth_net_device->name);
	free_netdev(eth_net_device);
	//unregister pci
	iounmap(priv->mmio_addr);
    pci_release_regions(priv->pciDev);
	pci_unregister_driver(&pciDriver);
	pci_disable_device(priv->pciDev);
	printk(KERN_INFO "DEBUG>> PCI Device: [%x]:[%x], unregistered and disabled\n", priv->pciDev->vendor, priv->pciDev->device);
    //INTEL_E1000_ETHERNET_DEVICE,
    
	return;
}

module_init(_init_module);
module_exit(_cleanup_module);

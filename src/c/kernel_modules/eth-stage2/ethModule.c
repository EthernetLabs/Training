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
MODULE_DESCRIPTION("Stage-2 Ethernet Linux PCI NIC driver");
MODULE_VERSION("0.1.3");

//ETH
static const struct net_device_ops eth_netdev_ops = {
	.ndo_open            = eth_open,
};

int eth_open(struct net_device *eth_dev)
{
	return 0;
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
	struct net_device *netdev;

    printk(KERN_INFO "nic_probe: Device found [%x]:[%x]\n", pdev->vendor, pdev->device);
    printk(KERN_INFO "nic_probe: Device IRQ: %d\n", pdev->irq);
    
	printk(KERN_INFO "Enabling Device: [%x]:[%x]\n", pdev->vendor, pdev->device);
	ret = pci_enable_device(pdev);//dd book p.314
	if (ret) {
    	printk(KERN_INFO "ret: %d\n", ret);
		return ret;
	}

	pciDev = pdev;

	return 1;
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
	eth_dev->flags     	|= IFF_NOARP;
	eth_dev->features  	|= NETIF_F_HW_CSUM;

	//This isn't necessary to register net_device
	priv = netdev_priv(eth_dev);
	memset(priv, 0, sizeof(struct eth_priv));

	return 0;
}


//Kernel module specific functions
static int _init_module(void)
{
	int i, result, ret = -ENOMEM;

	//proc
	pciModule_proc_entry = proc_create(ENTRY_NAME, S_IFREG | S_IRUGO| S_IWUSR, NULL, &procFileOps);
  	if (pciModule_proc_entry == NULL)
    	return ret;

	printk(KERN_INFO "/proc/%s created\n", ENTRY_NAME);

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
	
	if (eth_net_device == NULL)
		goto out;

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
	pci_unregister_driver(&pciDriver);
	pci_disable_device(pciDev);
	printk(KERN_INFO "DEBUG>> PCI Device: [%x]:[%x], unregistered and disabled\n", pciDev->vendor, pciDev->device);
    
	return;
}

module_init(_init_module);
module_exit(_cleanup_module);

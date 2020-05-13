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
#include <linux/moduleparam.h>
//proc
#include <linux/uaccess.h>
#include <linux/cred.h>
#include <linux/proc_fs.h>
#include "pciModule.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Weqaar's Linux PCI driver");
MODULE_VERSION("0.0.1");

typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

//PROC

/**
 * This funtion is called when the /proc file is read
 *
 */
static ssize_t procfs_read(struct file *filp,	/* see include/linux/fs.h   */
			     char *buffer,	/* buffer to fill with data */
			     size_t length,	/* length of the buffer     */
			     loff_t * offset)
{
	static int finished = 0;

	/* 
	 * We return 0 to indicate end of file, that we have
	 * no more information. Otherwise, processes will
	 * continue to read from us in an endless loop. 
	 */
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
	struct e1000_adapter *adapter = NULL;
	struct e1000_hw *hw;
	bool disable_dev = false;

    printk(KERN_INFO "nic_probe: Device found [%x]:[%x]\n", pdev->vendor, pdev->device);
    printk(KERN_INFO "nic_probe: Device IRQ: %d\n", pdev->irq);
    
	printk(KERN_INFO "Enabling Device: [%x]:[%x]\n", pdev->vendor, pdev->device);
	ret = pci_enable_device(pdev);//dd book p.314
	if (ret)
    	printk(KERN_INFO "ret: %d\n", ret);
		return ret;

	if (!adapter || disable_dev) {
		pci_disable_device(pdev);
    	printk(KERN_INFO "Device disabled: [%x]:[%x]\n", pdev->vendor, pdev->device);
	}
	return 1;
}

static void nic_remove(struct pci_dev *pdev)
{
    printk(KERN_INFO "DEBUG>> nic_remove\n");
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

//Kernel module specific functions
static int _init_module(void)
{

	int i, ret = -ENOMEM;

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

	pci_register_driver(&pciDriver);

	//access config space


	return 0;
}

static void _cleanup_module(void)
{
	int i;
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");

	//unregister proc
	pci_unregister_driver(&pciDriver);
	proc_remove(pciModule_proc_entry);
	__fptr_ptr.callfunc(KERN_INFO "/proc/%s removed\n", ENTRY_NAME);
    
	return;
}

module_init(_init_module);
module_exit(_cleanup_module);

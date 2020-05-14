/*
modulenet kernel driver - NIC
Stage 1
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
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/in6.h>
#include <asm/checksum.h>

#include "ethModule.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weqaar Janjua");
MODULE_DESCRIPTION("Stage-1 Ethernet Linux PCI NIC driver");
MODULE_VERSION("0.1.1");

//module parameters
static int lockup = 0;
module_param(lockup, int, 0);

static int timeout = ETH_TIMEOUT;
module_param(timeout, int, 0);

static int use_napi = 0;
module_param(use_napi, int, 0);

int pool_size = 8;
module_param(pool_size, int, 0);

typedef int (*_printk_ptr)(const char *fmt, ...); //define func pointer

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

//ETH
//Ethernet
static const struct net_device_ops eth_netdev_ops = {
	//.ndo_init			 = modulenet_init,
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
	//.nod_xdp_xmit = modulenet_xdp_xmit
};

static const struct header_ops _eth_header_ops = {
   	.create = eth_create_header,
	.validate = eth_validate_header
};

/*
 * Set up a device's packet pool.
 */
void eth_setup_pool(struct net_device *eth_dev)
{
	struct eth_priv *priv = netdev_priv(eth_dev);
	int i;
	struct eth_packet *pkt;

	priv->ppool = NULL;
	for (i = 0; i < pool_size; i++) {
		pkt = kmalloc (sizeof (struct eth_packet), GFP_KERNEL);
		if (pkt == NULL) {
			printk (KERN_NOTICE "Ran out of memory allocating packet pool\n");
			return;
		}
		pkt->eth_dev = eth_dev;
		pkt->next = priv->ppool;
		priv->ppool = pkt;
	}
}

/*
 * Enable and disable receive interrupts.
 */
static void eth_rx_ints(struct net_device *eth_dev, int enable)
{
	struct eth_priv *priv = netdev_priv(eth_dev);
	priv->rx_int_enabled = enable;
}

/*
 * Open and close
 */

int eth_open(struct net_device *eth_dev)
{
	/* request_region(), request_irq(), ....  (like fops->open) */

	/* 
	 * Assign the hardware address of the board: use "\0SNULx", where
	 * x is 0 or 1. The first byte is '\0' to avoid being a multicast
	 * address (the first byte of multicast addrs is odd).
	 */
	memcpy(eth_dev->dev_addr, "\0SNUL0", ETH_ALEN);
	if (eth_dev == eth_net_device)
		eth_dev->dev_addr[ETH_ALEN-1]++; /* \0SNUL1 */
	netif_start_queue(eth_dev);
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
 * Receive a packet: retrieve, encapsulate and pass over to upper levels
 */
void eth_rx(struct net_device *eth_dev, struct eth_packet *pkt)
{
	struct sk_buff *skb;
	struct eth_priv *priv = netdev_priv(eth_dev);

	/*
	 * The packet has been retrieved from the transmission
	 * medium. Build an skb around it, so upper layers can handle it
	 */
	skb = dev_alloc_skb(pkt->datalen + 2);
	if (!skb) {
		if (printk_ratelimit())
			printk(KERN_NOTICE "snull rx: low on mem - packet dropped\n");
		priv->stats.rx_dropped++;
		goto out;
	}
	skb_reserve(skb, 2); /* align IP on 16B boundary */  
	memcpy(skb_put(skb, pkt->datalen), pkt->data, pkt->datalen);

	/* Write metadata, and then pass to the receive level */
	skb->dev = eth_dev;
	skb->protocol = eth_type_trans(skb, eth_dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */
	priv->stats.rx_packets++;
	priv->stats.rx_bytes += pkt->datalen;
	netif_rx(skb);
  out:
	return;
}
    
/*
 * The poll implementation.
 */
static int eth_poll(struct napi_struct *napi, int budget)
{
	int npackets = 0;
	struct sk_buff *skb;
	struct eth_priv *priv = container_of(napi, struct eth_priv, napi);
	struct net_device *eth_dev = priv->eth_dev;
	struct eth_packet *pkt;
    
	while (npackets < budget && priv->rx_queue) {
		pkt = eth_dequeue_buf(eth_dev);
		skb = dev_alloc_skb(pkt->datalen + 2);
		if (! skb) {
			if (printk_ratelimit())
				printk(KERN_NOTICE "snull: packet dropped\n");
			priv->stats.rx_dropped++;
			eth_release_buffer(pkt);
			continue;
		}
		skb_reserve(skb, 2); /* align IP on 16B boundary */  
		memcpy(skb_put(skb, pkt->datalen), pkt->data, pkt->datalen);
		skb->dev = eth_dev;
		skb->protocol = eth_type_trans(skb, eth_dev);
		skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */
		netif_receive_skb(skb);
		
        	/* Maintain stats */
		npackets++;
		priv->stats.rx_packets++;
		priv->stats.rx_bytes += pkt->datalen;
		eth_release_buffer(pkt);
	}
	/* If we processed all packets, we're done; tell the kernel and reenable ints */
	if (! priv->rx_queue) {
		napi_complete(napi);
		eth_rx_ints(eth_dev, 1);
		return 0;
	}
	/* We couldn't process everything. */
	return npackets;
}
        
/*
 * The typical interrupt entry point
 */
static void eth_regular_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	int statusword;
	struct eth_priv *priv;
	struct eth_packet *pkt = NULL;
	/*
	 * As usual, check the "device" pointer to be sure it is
	 * really interrupting.
	 * Then assign "struct device *dev"
	 */
	struct net_device *eth_dev = (struct net_device *)dev_id;
	/* ... and check with hw if it's really ours */

	/* paranoid */
	if (!eth_dev)
		return;

	/* Lock the device */
	priv = netdev_priv(eth_dev);
	spin_lock(&priv->lock);

	/* retrieve statusword: real netdevices use I/O instructions */
	statusword = priv->status;
	priv->status = 0;
	if (statusword & ETH_RX_INTR) {
		/* send it to snull_rx for handling */
		pkt = priv->rx_queue;
		if (pkt) {
			priv->rx_queue = pkt->next;
			eth_rx(eth_dev, pkt);
		}
	}
	if (statusword & ETH_TX_INTR) {
		/* a transmission is over: free the skb */
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += priv->tx_packetlen;
		dev_kfree_skb(priv->skb);
	}

	/* Unlock the device and we are done */
	spin_unlock(&priv->lock);
	if (pkt) eth_release_buffer(pkt); /* Do this outside the lock! */
	return;
}

/*
 * A NAPI interrupt handler.
 */
static void eth_napi_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	int statusword;
	struct eth_priv *priv;

	/*
	 * As usual, check the "device" pointer for shared handlers.
	 * Then assign "struct device *dev"
	 */
	struct net_device *eth_dev = (struct net_device *)dev_id;
	/* ... and check with hw if it's really ours */

	/* paranoid */
	if (!eth_dev)
		return;

	/* Lock the device */
	priv = netdev_priv(eth_dev);
	spin_lock(&priv->lock);

	/* retrieve statusword: real netdevices use I/O instructions */
	statusword = priv->status;
	priv->status = 0;
	if (statusword & ETH_RX_INTR) {
		eth_rx_ints(eth_dev, 0);  /* Disable further interrupts */
		napi_schedule(&priv->napi);
	}
	if (statusword & ETH_TX_INTR) {
        	/* a transmission is over: free the skb */
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += priv->tx_packetlen;
		dev_kfree_skb(priv->skb);
	}

	/* Unlock the device and we are done */
	spin_unlock(&priv->lock);
	return;
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
	int len;
	char *data, shortpkt[ETH_ZLEN];
	struct eth_priv *priv = netdev_priv(eth_dev);
	
	data = skb->data;
	len = skb->len;
	if (len < ETH_ZLEN) {
		memset(shortpkt, 0, ETH_ZLEN);
		memcpy(shortpkt, skb->data, skb->len);
		len = ETH_ZLEN;
		data = shortpkt;
	}
	//eth_dev->trans_start = jiffies; /* save the timestamp */

	/* Remember the skb, so we can free it at interrupt time */
	priv->skb = skb;

	/* actual deliver of data is device-specific, and not shown here */
	eth_hw_tx(data, len, eth_dev);

	return 0; /* Our simple device can not fail */
}

/*
 * Deal with a transmit timeout.
 */
void eth_tx_timeout (struct net_device *eth_dev)
{
	struct eth_priv *priv = netdev_priv(eth_dev);

	priv->status = ETH_TX_INTR;
	eth_interrupt(0, eth_dev, NULL);
	priv->stats.tx_errors++;
	netif_wake_queue(eth_dev);
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

int eth_create_header(struct sk_buff *skb, struct net_device *eth_dev,
                unsigned short type, const void *daddr, const void *saddr,
                unsigned len)
{
	struct ethhdr *eth = (struct ethhdr *)skb_push(skb, ETH_HLEN);

	eth->h_proto = htons(type);
	memcpy(eth->h_source, saddr ? saddr : eth_dev->dev_addr, eth_dev->addr_len);
	memcpy(eth->h_dest,   daddr ? daddr : eth_dev->dev_addr, eth_dev->addr_len);
	eth->h_dest[ETH_ALEN-1]   ^= 0x01;   /* dest is us xor 1 */
	return (eth_dev->hard_header_len);
}

int	eth_set_mac_addr(struct net_device *eth_dev, void *addr) {

}

int	eth_validate_addr(struct net_device *eth_dev) {

}

/*
 * Buffer/pool management.
 */
struct eth_packet *eth_get_tx_buffer(struct net_device *eth_dev)
{
	struct eth_priv *priv = netdev_priv(eth_dev);
	unsigned long flags;
	struct eth_packet *pkt;
    
	spin_lock_irqsave(&priv->lock, flags);
	pkt = priv->ppool;
	priv->ppool = pkt->next;
	if (priv->ppool == NULL) {
		printk (KERN_INFO "Pool empty\n");
		netif_stop_queue(eth_dev);
	}
	spin_unlock_irqrestore(&priv->lock, flags);
	return pkt;
}


void eth_release_buffer(struct eth_packet *pkt)
{
	unsigned long flags;
	struct eth_priv *priv = netdev_priv(pkt->eth_dev);
	
	spin_lock_irqsave(&priv->lock, flags);
	pkt->next = priv->ppool;
	priv->ppool = pkt;
	spin_unlock_irqrestore(&priv->lock, flags);
	if (netif_queue_stopped(pkt->eth_dev) && pkt->next == NULL)
		netif_wake_queue(pkt->eth_dev);
}

void eth_enqueue_buf(struct net_device *eth_dev, struct eth_packet *pkt)
{
	unsigned long flags;
	struct eth_priv *priv = netdev_priv(eth_dev);

	spin_lock_irqsave(&priv->lock, flags);
	pkt->next = priv->rx_queue;  /* FIXME - misorders packets */
	priv->rx_queue = pkt;
	spin_unlock_irqrestore(&priv->lock, flags);
}

struct eth_packet *eth_dequeue_buf(struct net_device *eth_dev)
{
	struct eth_priv *priv = netdev_priv(eth_dev);
	struct eth_packet *pkt;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	pkt = priv->rx_queue;
	if (pkt != NULL)
		priv->rx_queue = pkt->next;
	spin_unlock_irqrestore(&priv->lock, flags);
	return pkt;
}

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
	if (ret) {
    	printk(KERN_INFO "ret: %d\n", ret);
		return ret;
	}

	pciDev = pdev;

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

//ETH
//static int eth_init(struct pci_dev *pdev, struct net_device *eth_dev)
void eth_init(struct net_device *eth_dev)
{
	struct eth_priv *priv;

	ether_setup(eth_dev); /* assign some of the fields */
	//net_device fields
	//eth_dev->name = "nic0";
	eth_dev->watchdog_timeo = timeout;
	eth_dev->netdev_ops = &eth_netdev_ops;
	eth_dev->header_ops = &_eth_header_ops;
	//eth_dev->irq = DEV_IRQ;
	/* keep the default flags, just add NOARP */
	eth_dev->flags           |= IFF_NOARP;
	eth_dev->features        |= NETIF_F_HW_CSUM;

	priv = netdev_priv(eth_dev);
	if (use_napi) {
		netif_napi_add(eth_dev, &priv->napi, eth_poll, 2);
	}
	memset(priv, 0, sizeof(struct eth_priv));
	spin_lock_init(&priv->lock);
	eth_rx_ints(eth_dev, 1); //enable receive interrupts
	eth_setup_pool(eth_dev);
	
	return 0;
}


//Kernel module specific functions
static int _init_module(void)
{

	int i, result, ret = -ENOMEM;
	unsigned long mmio_start, mmio_end, mmio_len, mmio_flags;
    void *ioaddr;

    eth_interrupt = use_napi ? eth_napi_interrupt : eth_regular_interrupt;

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

	//access config space
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
			printk("modulenet(out): error %i registering device \"%s\"\n", result, eth_net_device->name);
			return ret;
		}

        /* get PCI memory mapped I/O space base address from BAR1 */
        mmio_start = pci_resource_start(pciDev, 1);
        mmio_end = pci_resource_end(pciDev, 1);
        mmio_len = pci_resource_len(pciDev, 1);
        mmio_flags = pci_resource_flags(pciDev, 1);

		return ret;
}

static void _cleanup_module(void)
{
	int i;
    __fptr __fptr_ptr;
    __fptr_ptr.callfunc = printk;
	__fptr_ptr.callfunc(KERN_ALERT "__JANJUA__ EXITING!\n");

	//unregister proc
	unregister_netdev(eth_net_device);
	free_netdev(eth_net_device);
	pci_unregister_driver(&pciDriver);
	pci_disable_device(pciDev);
	proc_remove(pciModule_proc_entry);
	__fptr_ptr.callfunc(KERN_INFO "/proc/%s removed\n", ENTRY_NAME);
    
	return;
}

module_init(_init_module);
module_exit(_cleanup_module);

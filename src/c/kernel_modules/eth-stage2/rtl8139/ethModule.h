#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/pci.h>

/* PROC
*/
#define ENTRY_NAME          "ethModule-stage2"
#define DRIVER_NAME         ENTRY_NAME
#define PERMS               0644
#define PARENT              NULL
#define PROCFS_MAX_SIZE 	2048
#define INTEL_E1000_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_VENDOR_ID_WEITEK)}
#define RTL_8139_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_REALTEK, PCI_DEVICE_ID_REALTEK_8139)}

//PROC
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static struct proc_dir_entry *pciModule_proc_entry;

//PCI
static struct pci_dev *pciDev;
static struct pci_driver pciDriver;

//ETH
#define ETH_TIMEOUT 5   /* In jiffies */
#define DEV_NAME "nic0"

static struct net_device *eth_net_device;

static struct eth_priv {
    struct pci_dev *pciDev;
	struct net_device_stats stats;
	int status;
    void *mmio_addr; /* memory mapped I/O addr */
    unsigned long regs_len; /* length of I/O or MMI/O region */
};

static struct eth_priv *priv;

int eth_open(struct net_device *);
int eth_release(struct net_device *);
int eth_config(struct net_device *, struct ifmap *);
static void eth_hw_tx(char *, int, struct net_device *);
int eth_tx(struct sk_buff *, struct net_device *);
static void eth_tx_timeout (struct net_device *);
int eth_ioctl(struct net_device *, struct ifreq *, int);
struct net_device_stats *eth_stats(struct net_device *);
int	eth_set_mac_addr(struct net_device *, void *);
int	eth_validate_addr(struct net_device *);

//KERNEL
typedef int (*_printk_ptr)(const char *fmt, ...);

typedef struct _fps {
    _printk_ptr callfunc;
}__fptr;

//https://elixir.bootlin.com/linux/v5.1/source/include/linux/pci_ids.h#L2971
//https://elixir.bootlin.com/linux/latest/source/drivers/net/ethernet/intel/e1000/e1000_main.c
static const struct pci_device_id intel_rtl_nics_table[] = {
    RTL_8139_ETHERNET_DEVICE,
    { 0, },
};

MODULE_DEVICE_TABLE(pci, intel_rtl_nics_table);


#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/pci.h>

/* PROC
*/
#define ENTRY_NAME          "ethModule"
#define PERMS               0644
#define PARENT              NULL
#define PROCFS_MAX_SIZE 	2048
//#define INTEL_E1000_ETHERNET_DEVICE(device_id) {PCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id)}
//#define RTL_8139_ETHERNET_DEVICE(device_id) {PCI_DEVICE(PCI_VENDOR_ID_REALTEK, PCI_DEVICE_ID_REALTEK_8139)}
#define INTEL_E1000_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_VENDOR_ID_WEITEK)}
#define RTL_8139_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_REALTEK, PCI_DEVICE_ID_REALTEK_8139)}

//PROC
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static struct proc_dir_entry *pciModule_proc_entry;

//PCI
static struct pci_dev *pciDev; // we do not use this for the moment
static struct pci_driver pciDriver;

//ETH
#define ETH_TIMEOUT 5   /* In jiffies */
#define DEV_NAME "nic0"
#define DEV_IRQ 32
#define ETH_RX_INTR 0x0001
#define ETH_TX_INTR 0x000
//static struct net_device *rtl8139_dev;
static struct net_device *eth_net_device;

static struct eth_packet {
	struct eth_packet *next;
	struct net_device *eth_dev;
	int	datalen;
	u8 data[ETH_DATA_LEN];
};

static struct eth_priv {
	struct net_device_stats stats;
	int status;
	struct eth_packet *ppool;
	struct eth_packet *rx_queue;  /* List of incoming packets */
	int rx_int_enabled;
	int tx_packetlen;
	u8 *tx_packetdata;
	struct sk_buff *skb;
	spinlock_t lock;
	struct net_device *eth_dev;
	struct napi_struct napi;
    void *mmio_addr; /* memory mapped I/O addr */
    unsigned long regs_len; /* length of I/O or MMI/O region */
};

void eth_setup_pool(struct net_device *);
static void eth_rx_ints(struct net_device *, int);
int eth_open(struct net_device *);
int eth_release(struct net_device *);
int eth_config(struct net_device *, struct ifmap *);
void eth_rx(struct net_device *, struct eth_packet *);
static int eth_poll(struct napi_struct *, int);
static void eth_regular_interrupt(int, void *, struct pt_regs *);
static void eth_napi_interrupt(int, void *, struct pt_regs *);
static void eth_hw_tx(char *, int, struct net_device *);
int eth_tx(struct sk_buff *, struct net_device *);
static void eth_tx_timeout (struct net_device *);
static void (*eth_interrupt)(int, void *, struct pt_regs *);
int eth_ioctl(struct net_device *, struct ifreq *, int);
struct net_device_stats *eth_stats(struct net_device *);
int	eth_set_mac_addr(struct net_device *, void *);
bool eth_validate_header(const char *, unsigned int);
int	eth_validate_addr(struct net_device *);
int eth_create_header(struct sk_buff *, struct net_device *, unsigned short, const void *, const void *, unsigned);
struct eth_packet *eth_get_tx_buffer(struct net_device *);
void eth_release_buffer(struct eth_packet *);
void eth_enqueue_buf(struct net_device *, struct eth_packet *);
struct eth_packet *eth_dequeue_buf(struct net_device *);


//KERNEL
static void _call_printk(struct work_struct *);

//https://elixir.bootlin.com/linux/v5.1/source/include/linux/pci_ids.h#L2971
//https://elixir.bootlin.com/linux/latest/source/drivers/net/ethernet/intel/e1000/e1000_main.c
static const struct pci_device_id intel_rtl_nics_table[] = {
    //INTEL_E1000_ETHERNET_DEVICE(0x100E),
    //RTL_8139_ETHERNET_DEVICE(0x8139),
    INTEL_E1000_ETHERNET_DEVICE,
    //RTL_8139_ETHERNET_DEVICE,
    { 0, },
};

MODULE_DEVICE_TABLE(pci, intel_rtl_nics_table);


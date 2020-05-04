#include <linux/netdevice.h>

#define ETH_TIMEOUT 5   /* In jiffies */
#define DEV_NAME nic0
#define DEV_IRQ 10

/* PCI
*  NIC: RTL8139
*  
*/
#define NIC_VENDOR_ID   0x10EC
#define NIC_DEVICE_ID   0x8139

extern struct net_device *eth_devs[];

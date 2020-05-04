#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/pci.h>

/* PCI
*  NIC: RTL8139
*  
*/
#define NIC_VENDOR_ID   0x10EC
#define NIC_DEVICE_ID   0x8139

/* PROC
*/
#define ENTRY_NAME          "pciModule"
#define PERMS               0644
#define PARENT              NULL
#define PROCFS_MAX_SIZE 	2048
//#define INTEL_E1000_ETHERNET_DEVICE(device_id) {PCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id)}
//#define RTL_8139_ETHERNET_DEVICE(device_id) {PCI_DEVICE(PCI_VENDOR_ID_REALTEK, PCI_DEVICE_ID_REALTEK_8139)}
#define INTEL_E1000_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_VENDOR_ID_WEITEK)}
#define RTL_8139_ETHERNET_DEVICE {PCI_DEVICE(PCI_VENDOR_ID_REALTEK, PCI_DEVICE_ID_REALTEK_8139)}

static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static struct proc_dir_entry *pciModule_proc_entry;
static struct pci_dev *pciDev;
static struct pci_driver pciDriver;
static void _call_printk(struct work_struct *);

//https://elixir.bootlin.com/linux/v5.1/source/include/linux/pci_ids.h#L2971
//https://elixir.bootlin.com/linux/latest/source/drivers/net/ethernet/intel/e1000/e1000_main.c
static const struct pci_device_id intel_rtl_nics_table[] = {
    //INTEL_E1000_ETHERNET_DEVICE(0x100E),
    //RTL_8139_ETHERNET_DEVICE(0x8139),
    INTEL_E1000_ETHERNET_DEVICE,
    RTL_8139_ETHERNET_DEVICE,
    { 0, },
};

MODULE_DEVICE_TABLE(pci, intel_rtl_nics_table);


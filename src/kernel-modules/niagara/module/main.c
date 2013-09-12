#include "niagara_module.h"
#include "cpld.h"
#include "cpu.h"
#include "pci_cards.inc"

card_t cards[MAX_CARD];
int maxcard = 0;

static int niagara_major;
static struct class *niagara_class;
#ifdef CONFIG_NIAGARA_IOCTL
extern struct file_operations niagara_fops;
#include <linux/cdev.h>
static struct cdev cdev;
#endif


static int __init niagara_init(void)
{
	int pci, rc, i;
	dev_t dev = 0;

	MSG_TTY("Version %d.%db%d started",
	    NIAGARA_VERSION_MAJOR,
	    NIAGARA_VERSION_MINOR,
	    NIAGARA_VERSION_BUILD);
// scan PCI for known devices
	for (pci = 0; pci_cards[pci].vendor; pci++) 
	if(supported_card(pci_cards+pci))
	{
		struct pci_dev *pci_dev = NULL;
		int port_in_card = 0;
		for (;; ) {
			pci_dev = pci_get_subsys(pci_cards[pci].vendor, pci_cards[pci].device,
						 pci_cards[pci].ss_vendor, pci_cards[pci].ss_device, pci_dev);
			if (pci_dev == NULL) break;
			if (port_in_card == 0) { // new card
				if (maxcard >= MAX_CARD) {
					MSG_TTY("Too many cards, %d max\n", MAX_CARD);
					return -E2BIG;
				}
			}
			cards[maxcard].pci_dev[port_in_card] = pci_dev;
			if (++port_in_card == pci_cards[pci].num_ports) { // card is finished
				cards[maxcard].flags = pci_cards[pci].flags;
				cards[maxcard].num_ports = port_in_card;
				snprintf(cards[maxcard].name, sizeof(cards[maxcard].name), "%s", pci_cards[pci].name);
				MSG_TTY("%s (%d ports %s)", cards[maxcard].name, cards[maxcard].num_ports, flag2str(cards[maxcard].flags));
				if (cpld_validate(maxcard)) {
					MSG_TTY("Cannot get response from CPLD of %s", cards[maxcard].name);
					port_in_card = 0;
					continue;
				}
				cards[maxcard].cpld_id = cpld_read(maxcard, ID_R);
				cards[maxcard].oem_id = cpu_read(maxcard, OEM_ID_REG);
				cards[maxcard].product_id = cpu_read(maxcard, PRODUCT_ID_REG);
				cards[maxcard].product_rev = cpu_read(maxcard, PRODUCT_REV_REG);
				cards[maxcard].firmware_rev = cpu_read(maxcard, FW_ID_REG);
				cards[maxcard].secondary_firmware_rev = cpu_read(maxcard, 69);
#ifdef CONFIG_NIAGARA_CPLD_SPI
				cards[maxcard].avr_sig = spi_read_sig(maxcard);
				DBG("avr_sig=%X", cards[maxcard].avr_sig);
#endif
				maxcard++;
				port_in_card = 0;
			}
		}
	}
	MSG_TTY("%d card(s) found", maxcard);
	if (maxcard == 0) return -ENXIO;
//poopulate /dev
	rc = alloc_chrdev_region(&dev, 0, maxcard, "niagara");
	if (rc) return rc;
	niagara_major = MAJOR(dev);
	niagara_class = class_create(THIS_MODULE, "niagara");
	if (IS_ERR(niagara_class)) return PTR_ERR(niagara_class);
#ifdef CONFIG_NIAGARA_IOCTL
	cdev_init(&cdev, &niagara_fops);
	cdev.owner = THIS_MODULE;
	rc = cdev_add(&cdev, dev, maxcard);
	if (rc) return rc;
#endif
	for (i = 0; i < maxcard; i++) {
		struct device *device = device_create(niagara_class, NULL, MKDEV(niagara_major, i), cards + i, "niagara%d", i); //2.6.27
		if (IS_ERR(device)) return PTR_ERR(device);
#ifdef CONFIG_NIAGARA_SYSFS
		rc = sysfs_populate(device);
		if (rc) return rc;
#endif
	}
#ifdef CONFIG_NIAGARA_PROCFS
	procfs_create();
#endif
	for(i=0;i<maxcard;i++)
	 try_module_get(cards[i].pci_dev[0]->dev.driver->owner);
	return 0;
}
module_init(niagara_init);


static void __exit niagara_destroy(void)
{
	int i, j;
	for(i=0;i<maxcard;i++)
	  module_put(cards[i].pci_dev[0]->dev.driver->owner);
	

#ifdef CONFIG_NIAGARA_IOCTL
	cdev_del(&cdev);
#endif
	for (i = 0; i < maxcard; i++)
		device_destroy(niagara_class, MKDEV(niagara_major, i));
	class_destroy(niagara_class);
	unregister_chrdev_region(MKDEV(niagara_major, 0), maxcard);
#ifdef CONFIG_NIAGARA_PROCFS
	procfs_destroy();
#endif
// stop all heartbeat and lfd timers
	for (i = 0; i < maxcard; i++)
		for (j = 0; j < cards[i].num_ports / 2; j++) {
			NiagaraSetAttribute(i, j, "heartbeat", 0);
			NiagaraSetAttribute(i, j, "lfd", 0);
		}
	MSG("unloaded");
}
module_exit(niagara_destroy);
MODULE_LICENSE("GPL"); // we need it for sysfs
MODULE_AUTHOR("sergiyg@interfacemasters.com");

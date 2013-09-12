#include "niagara_module.h"
#ifdef CONFIG_NIAGARA_PROCFS
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

typedef struct {
	const char *	name;
	unsigned	mode;
} attribute_t;

#define NIAGARA_DRIVER_ATTRIBUTE(_name, _mode) { # _name, _mode },
static attribute_t driver_attributes[] = {
#include "niagara_driver_attributes.h"
#undef NIAGARA_DRIVER_ATTRIBUTE
};
#define NIAGARA_CARD_ATTRIBUTE(_name, _mode) { # _name, _mode },
static attribute_t card_attributes[] = {
#include "niagara_card_attributes.h"
#undef NIAGARA_CARD_ATTRIBUTE
};
#define NIAGARA_SEGMENT_ATTRIBUTE(_name, _mode) { # _name, _mode },
static attribute_t segment_attributes[] = {
#include "niagara_segment_attributes.h"
#undef NIAGARA_SEGMENT_ATTRIBUTE
};

static int proc_read(char *buf, char **start, off_t off, int count, int *eof, void *data)
{
	int rc, card = 0, segment = 0;
	unsigned value;
	struct proc_dir_entry *param = (struct proc_dir_entry *)data; // data points to our proc_dir_entry

	if (off > 0) return 0;
	if (strcmp(param->parent->name, "niagara")) {
		if (strcmp(param->parent->parent->name, "niagara")) { // segment
			segment = atoi(param->parent->name);
			card = atoi(param->parent->parent->name);
		} else { //card
			card = atoi(param->parent->name);
		}
	}
	rc = NiagaraGetAttribute(card, segment, param->name, &value);
	if (rc) return rc;
	return scnprintf(buf, count, "%X\n", value);
}
static int proc_write(struct file *file, const char *buffer, unsigned long count, void *data)
{
	int rc, card = 0, segment = 0;
	char cmd[64], *eptr;
	unsigned value;
	struct proc_dir_entry *param = (struct proc_dir_entry *)data; // data points to our proc_dir_entry

	if (count > sizeof(cmd)) count = sizeof(cmd);
	if (copy_from_user(cmd, buffer, count)) return -EFAULT;
	value = simple_strtoul(cmd, &eptr, 16);
	if (eptr == cmd) return -EINVAL;
	if ((*eptr != 0) && (*eptr != '\n')) return -EINVAL;
	if (strcmp(param->parent->name, "niagara")) {
		if (strcmp(param->parent->parent->name, "niagara")) { // segment
			segment = atoi(param->parent->name);
			card = atoi(param->parent->parent->name);
		} else { //card
			card = atoi(param->parent->name);
		}
	}
	rc = NiagaraSetAttribute(card, segment, param->name, value);
	if (rc) return rc;
	return count;
}
static int proc_read_supported_cards(char *buf, char **start, off_t off, int count, int *eof, void *data)
{
	int i, wrote = 0;

	if (off > 0) return 0;
	for (i = 0; pci_cards[i].vendor; i++) 
	if(supported_card(pci_cards+i))
	{
		int portion = scnprintf(buf + wrote, count - wrote, "%s\t%d port %s\n", pci_cards[i].name, pci_cards[i].num_ports, flag2str(pci_cards[i].flags));
		wrote += portion;
		if (portion < 10) break;
	}
	return wrote;
}
static int proc_read_name(char *buf, char **start, off_t off, int count, int *eof, void *data)
{
	if (off > 0) return 0;
	return scnprintf(buf, count, "%s\n", (char *)data);
}

static struct proc_dir_entry *niagara_root;

static struct proc_dir_entry *create_attribute(attribute_t *a, struct proc_dir_entry *parent, read_proc_t *read, write_proc_t *write)
{
	struct proc_dir_entry *entry;

	entry = create_proc_entry(a->name, a->mode, parent);
	if (entry == NULL) return NULL;
	entry->read_proc = read;
	entry->write_proc = write;
	entry->data = entry;
	entry->nlink = 1;
	return entry;
}

int __init procfs_create(void)
{
	int i, j, a;

	niagara_root = proc_mkdir("niagara", NULL);
	create_proc_read_entry("supported_cards", 0444, niagara_root, proc_read_supported_cards, NULL);
	for (a = 0; a < sizeof(driver_attributes) / sizeof(driver_attributes[0]); a++)
		create_attribute(driver_attributes + a, niagara_root, proc_read, NULL);
	for (i = 0; i < maxcard; i++) {
		struct proc_dir_entry *card_root = proc_mkdir(itoa(i), niagara_root);
		create_proc_read_entry("name", 0444, card_root, proc_read_name, cards[i].name);
		for (a = 0; a < sizeof(card_attributes) / sizeof(card_attributes[0]); a++)
			create_attribute(card_attributes + a, card_root, proc_read, NULL);
		for (j = 0; j < cards[i].num_ports / 2; j++) {
			struct proc_dir_entry *segment_root = proc_mkdir(itoa(j), card_root);
			for (a = 0; a < sizeof(segment_attributes) / sizeof(segment_attributes[0]); a++)
				create_attribute(segment_attributes + a, segment_root, proc_read, proc_write);
		}
	}
	return 0;
}

int procfs_destroy(void)
{
	int i, j, a;
	char str[256];

	for (i = 0; i < maxcard; i++) {
		for (j = 0; j < cards[i].num_ports / 2; j++) {
			for (a = 0; a < sizeof(segment_attributes) / sizeof(segment_attributes[0]); a++) {
				snprintf(str, sizeof(str), "niagara/%X/%X/%s", i, j, segment_attributes[a].name);
				remove_proc_entry(str, NULL);
			}
			snprintf(str, sizeof(str), "niagara/%X/%X", i, j);
			remove_proc_entry(str, NULL);
		}
		for (a = 0; a < sizeof(card_attributes) / sizeof(card_attributes[0]); a++) {
			snprintf(str, sizeof(str), "niagara/%X/%s", i, card_attributes[a].name);
			remove_proc_entry(str, NULL);
		}
		snprintf(str, sizeof(str), "niagara/%X/name", i);
		remove_proc_entry(str, NULL);
		snprintf(str, sizeof(str), "niagara/%X", i);
		remove_proc_entry(str, NULL);
	}
	for (a = 0; a < sizeof(driver_attributes) / sizeof(driver_attributes[0]); a++) {
		snprintf(str, sizeof(str), "niagara/%s", driver_attributes[a].name);
		remove_proc_entry(str, NULL);
	}
	remove_proc_entry("supported_cards", niagara_root);
	remove_proc_entry("niagara", NULL);
	return 0;
}
#endif

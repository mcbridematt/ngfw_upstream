#!/usr/bin/make
# Makefile for building Linux Broadcom 10-Gigabit ethernet driver as a module.

ifeq (,$(BUILD_KERNEL))
BUILD_KERNEL=$(shell uname -r)
endif

KVER = $(BUILD_KERNEL)

# PREFIX may be set by the RPM build to set the effective root.
PREFIX =

KERNEL_DIR = /usr/src/linux #-headers-$(KVER)

MAN_DIR = $(PREFIX)/usr/share/man/man4

# generated include files
INIT_VAL_C = bnx2x_init_values_e1.c bnx2x_init_values_e1h.c
IDLE_CHK_H = bnx2x_self_test.h
REG_DUMP_H = bnx2x_dump.h
REG_HSI_H = bnx2x_reg.h bnx2x_fw_defs.h bnx2x_hsi.h
CNIC_INC = ../../bnx2/src/cnic_if.h
INIT_OPS_H = bnx2x_init.h bnx2x_init_ops.h

SOURCES = bnx2x_main.c bnx2x_link.c bnx2x.h bnx2x_link.h bnx2x_compat.h $(INIT_OPS_H) bnx2x_fw_file_hdr.h

obj-m += bnx2x.o
bnx2x-objs = bnx2x_main.o bnx2x_link.o $(INIT_VAL_C:%.c=%.o)

EXTRA_CFLAGS += -Werror
ifeq ($(NX2_BOOT_DISK),1)
	EXTRA_CFLAGS += -DBNX2X_DRIVER_DISK
endif

ifeq ($(NX2_DISABLE_GRO),1)
	EXTRA_CFLAGS += -DBCM_DISABLE_GRO
endif

# targets and rules
.PHONY: all modules_install docs_install clean install

all default: $(obj-m)

$(obj-m): $(SOURCES) $(INIT_VAL_C) $(IDLE_CHK_H) $(REG_DUMP_H) $(REG_HSI_H) $(CNIC_INC) $(SUSE_SUPPORT)
	$(MAKE) -C $(KERNEL_DIR) M=`pwd` modules

modules_install: $(obj-m)
	make -C $(KERNEL_DIR) M=`pwd` INSTALL_MOD_PATH=$(PREFIX) INSTALL_MOD_DIR=$(DRV_DIR) modules_install
	@if [ "$(PREFIX)" = "" ] ;\
		then /sbin/depmod -a ;\
		else echo " *** Run '/sbin/depmod -a' to update the module database." ;\
	fi

docs_install:
	gzip -c bnx2x.4 > bnx2x.4.gz
	install -m 644 bnx2x.4.gz $(MAN_DIR)

clean:
	make -C $(KERNEL_DIR) M=`pwd` clean
	@rm -f *.fw *.ihex

install: modules_install docs_install

Module.supported:
	echo "bnx2x.ko external" > $@

# generate the include files
-include Makefile.gen

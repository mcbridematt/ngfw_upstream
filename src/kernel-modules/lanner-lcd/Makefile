# Kernel Version Check
KVER  := $(shell uname -r | cut -c1-3 | sed 's/2\.[56]/2\.6/')
KVERSUB := $(shell uname -r | cut -c5-6)
KVER3 :=$(shell uname -r | cut -c1-1)
# Makefile for a basic kernel module - 2.4.x
KINC=
ifeq ($(KINC),)
KINC  := $(shell uname -r)
endif
CC    := gcc
MODCFLAGS := -DMODULE -D__KERNEL__ -DLINUX -DOLDKERNEL -O -I/usr/src/linux-$(KINC)/include

# Makefile for a basic kernel module - 2.6.x
obj-m := plcm_drv.o
KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

default:
ifeq ($(wildcard /dev/plcm_drv),)
	mknod /dev/plcm_drv c 248 0
endif
ifeq ($(KVER3),3)
	$(MAKE) -C $(KDIR) M=$(PWD) modules
endif
ifeq ($(KVER),2.6)
	$(MAKE) -C $(KDIR) M=$(PWD) modules
endif
ifeq ($(KVER),2.4)
	$(CC) $(MODCFLAGS) -c plcm_drv.c
endif
clean:
ifeq ($(KVER3),3)
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
ifeq ($(KVER),2.6)
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
ifeq ($(KVER),2.4)
	rm -f *.o *.ko
endif


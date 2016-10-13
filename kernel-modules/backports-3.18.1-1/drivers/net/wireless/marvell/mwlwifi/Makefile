mwlwifi-y		+= main.o
mwlwifi-y		+= mac80211.o
mwlwifi-y		+= fwdl.o
mwlwifi-y		+= fwcmd.o
mwlwifi-y		+= tx.o
mwlwifi-y		+= rx.o
mwlwifi-y		+= isr.o
mwlwifi-$(CONFIG_THERMAL)	+= thermal.o
mwlwifi-$(CONFIG_DEBUG_FS)	+= debugfs.o

obj-$(CPTCFG_MWLWIFI)	+= mwlwifi.o

ccflags-y += -D__CHECK_ENDIAN__

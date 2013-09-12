all: user_api/util module/niagara.ko

module/niagara.ko: include/niagara_config.h
	make -j -C module modules
user_api/util:
	make -j -C user_api util

insmod: module/niagara.ko
	sudo insmod $<
rmmod:
	sudo rmmod niagara

install: 
#	make -C module modules_install
	make -C user_api install
	install -m 0644 udev/* /lib/udev/rules.d
uninstall:
#	rm -rf /lib/modules/`uname -r`/niagara.ko
	make -C user_api uninstall
clean:
	make -C module   clean
	make -C user_api clean
tar: clean
	cd .. ; tar -cvf universal-driver.0.4.tar --exclude='.git/*' $(shell basename ${CURDIR})

obj-m += jiffies_module.o

all:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(PWD) modules
clean:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(PWD) clean
install: 
	sudo insmod jiffies_module.ko
remove:
	sudo rmmod jiffies_module

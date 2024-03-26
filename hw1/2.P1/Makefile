obj-m += jiffies_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install: 
	sudo insmod jiffies_module.ko
remove:
	sudo rmmod jiffies_module

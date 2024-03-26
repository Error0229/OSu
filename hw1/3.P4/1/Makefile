obj-m += ds_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install:
	sudo insmod ds_module.ko
remove:
	sudo rmmod ds_module

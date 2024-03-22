obj-m += task_module.o

all:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(PWD) modules
clean:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(PWD) clean
install:
	sudo insmod task_module.ko
remove:
	sudo rmmod task_module

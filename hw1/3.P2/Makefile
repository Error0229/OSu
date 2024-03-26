obj-m += task_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install:
	sudo insmod task_module.ko
remove:
	sudo rmmod task_module

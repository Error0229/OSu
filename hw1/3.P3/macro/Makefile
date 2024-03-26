obj-m += pid_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install:
	sudo insmod pid_module.ko
remove:
	sudo rmmod pid_module

obj-m += colallocator.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

test:
	sudo dmesg -C
	make clean
	make 
	sudo insmod colallocator.ko
	sudo rmmod colallocator.ko
	sudo dmesg
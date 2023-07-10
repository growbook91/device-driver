KERNDIR=/lib/modules/$(shell uname -r)/build
obj-m+=driver.o
objs+=driver.o
PWD=$(shell pwd)

default:
	make -C $(KERNDIR) M=$(PWD) modules

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm -rf *.ko
	rm -rf *.o
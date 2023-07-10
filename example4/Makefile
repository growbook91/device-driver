KERNDIR=/lib/modules/$(shell uname -r)/build
obj-m+=skeleton26.o
objs+=skeleton26.o
APP=userapp
PWD=$(shell pwd)

default:$(APP)
	make -C $(KERNDIR) M=$(PWD) modules

CC := gcc
%.c%:
	${CC} -o $@ $^

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm -rf *.ko
	rm -rf *.o
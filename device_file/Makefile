ifdef ARCH
	KERNDIR=/home/gmlee/projects/RDMS/yocto/build/tmp/work/imx8mp_lpddr4_evk-poky-linux/linux-revros/5.10.52+gitAUTOINC+766a9d825a-r0/build
else
	KERNDIR=/lib/modules/$(shell uname -r)/build
endif


obj-m+=driver.o

PWD=$(shell pwd)

default:
	make -C $(KERNDIR) M=$(PWD) modules

%.c%:
	${CC} -o $@ $^

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm -rf *.ko
	rm -rf *.o

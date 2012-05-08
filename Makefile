#Makefile
obj-m := drv.o

#内核根目录
KDIR := /lib/modules/3.2.0-23-generic-pae/build/

#当前目录
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -r *.o *.ko *.symvers *.order *.mod.c .*.cmd .tmp_versions

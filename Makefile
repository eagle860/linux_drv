#Makefile
obj-m := drv.o

#�ں˸�Ŀ¼
KDIR := /lib/modules/3.2.0-23-generic-pae/build/

#��ǰĿ¼
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -r *.o *.ko *.symvers *.order *.mod.c .*.cmd .tmp_versions

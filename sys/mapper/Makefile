obj-m += mymap2.o

ccflags-y += -g -O0 -DCONFIG_KGDB

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


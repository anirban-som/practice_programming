BINARY		:= my_char_dev
KERNELDIR	:= /lib/modules/$(shell uname -r)/build
KMOD_DIR	:= $(shell pwd)
TARGET_PATH	:= /lib/modules/$(shell uname -r)/kernel/drivers/char

OBJECTS	:= main.o

obj-m	+= $(BINARY).o

$(BINARY)-y	:= $(OBJECTS)
$(BINARY).ko:
	$(MAKE) -C $(KERNELDIR) M=$(KMOD_DIR) modules

install:
	cp $(BINARY).ko $(TARGET_PATH)
	depmod -a
	insmod $(BINARY).ko
uninstall:
	rm $(TARGET_PATH)/$(BINARY).ko
	depmod -a
	rmmod $(BINARY)

clean:
	make -C $(KERNELDIR) M=$(KMOD_DIR) clean
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers *.mod


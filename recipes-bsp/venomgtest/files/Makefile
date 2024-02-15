include Kbuild
ifeq ($(KBUILD_MODULES),)


obj-m := venomgtest.ko

SRC := $(shell pwd)

all: venomgtest.ko

venomgtest: venomgtest.ko
venomgtest.ko:
	@echo "Build venomgtest driver..."
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install
	@echo ""
	@echo "SUCCESS"
	@echo ""

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c

endif # !kbuild

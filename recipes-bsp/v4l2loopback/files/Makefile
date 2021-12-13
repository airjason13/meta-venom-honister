include Kbuild
ifeq ($(KBUILD_MODULES),)

obj-m := v4l2loopback.ko

SRC := $(shell pwd)

#KERNELRELEASE	?= `uname -r`
#KERNEL_DIR	?= /lib/modules/$(KERNELRELEASE)/build
#PWD		:= $(shell pwd)

#PREFIX ?= /usr/local
#BINDIR  = $(PREFIX)/bin
#MANDIR  = $(PREFIX)/share/man
#MAN1DIR = $(MANDIR)/man1
#INSTALL = install
#INSTALL_PROGRAM = $(INSTALL) -p -m 755
#INSTALL_DIR     = $(INSTALL) -p -m 755 -d
#INSTALL_DATA    = $(INSTALL) -m 644

MODULE_OPTIONS = devices=2

##########################################
# note on build targets
#
# module-assistant makes some assumptions about targets, namely
#  <modulename>: must be present and build the module <modulename>
#                <modulename>.ko is not enough
# install: must be present (and should only install the module)
#
# we therefore make <modulename> a .PHONY alias to <modulename>.ko
# and remove utils-installation from 'install'
# call 'make install-all' if you want to install everything
##########################################




all: v4l2loopback.ko 

v4l2loopback: v4l2loopback.ko
v4l2loopback.ko:
	@echo "Building v4l2-loopback driver..."
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install
	@echo ""
	@echo "SUCCESS (if you got 'SSL errors' above, you can safely ignore them)"
	@echo ""


clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c




endif # !kbuild

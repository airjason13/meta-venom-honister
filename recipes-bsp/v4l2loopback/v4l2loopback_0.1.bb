SUMMARY = "Example of how to build an external Linux kernel module"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

inherit module

SRC_URI = "file://Makefile \
           file://AUTHORS \
           file://ChangeLog \
           file://currentversion.sh \
           file://dkms.conf \
           file://doc/ \
           file://examples/ \
           file://Kbuild \
           file://Makefile \
           file://Makefile.manual \
           file://man/ \
           file://NEWS \
           file://README.md \
           file://release.sh \
           file://tests \
           file://tmp/ \
           file://TODO \
           file://udev/ \
           file://utils \
           file://v4l2loopback.c \
           file://v4l2loopback_formats.h \
           file://v4l2loopback.h \
           file://vagrant/ \
           file://COPYING \
          "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "kernel-module-v4l2loopback"

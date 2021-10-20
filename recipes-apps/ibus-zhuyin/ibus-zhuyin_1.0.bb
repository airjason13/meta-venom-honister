SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "ibus-zhuyin"
LICENSE = "GPL-3.0"
LIC_FILES_CHKSUM = "file://COPYING;md5=5d65073d0b1fcc7e4e6dff05af4fec48"

SRC_URI = "git://github.com/fourdollars/ibus-zhuyin;protocol=https"

PV = "0.1.0+git${SRCPV}"
SRCREV = "9c156569a992f1243018661be3fcee4983874e8f"
DEPENDS = "gtk+ gtk+3 ibus"

S = "${WORKDIR}/git"

do_configure:prepend() {
    touch ${S}/ABOUT-NLS
}


do_configure() {
   OECONF
}

do_compile() {
    make
}


inherit autotools gettext pkgconfig

EXTRA_OECONF = "--prefix=/usr --libexecdir=/usr/lib/ibus CFLAGS=-g CXXFLAGS=-g"

FILE_${PN} += "${datadir}/ibus/* /usr/lib/ibus/*"

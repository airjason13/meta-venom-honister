SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://raspberrypi-swd-2.cfg "

do_install:append() {
	install -m 0444 ${WORKDIR}/raspberrypi-swd-2.cfg ${D}${datadir}/openocd/scripts/interface/
}

FILES:${PN} +="${datadir}/openocd/scripts/interface/"



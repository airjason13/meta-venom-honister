SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://raspberrypi-swd-2.cfg "

do_install_append() {
	install -m 0444 ${WORKDIR}/raspberrypi-swd-2.cfg ${D}${datadir}/openocd/scripts/interface/
}

#FILES_${PN}="${datadir}/openocd/scripts/interface/"



SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://wave.svg "

do_install:append() {
	#install -m 0444 ${WORKDIR}/wave.svg ${D}${datadir}/lxdm/themes/Industrial
	install -m 0444 ${WORKDIR}/lxdm.conf ${D}${sysconfdir}/lxdm/lxdm.conf
}



SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://dnsmasq.conf "

do_install:append() {
	install -m 0444 ${WORKDIR}/dnsmasq.conf ${D}${sysconfdir}/
}




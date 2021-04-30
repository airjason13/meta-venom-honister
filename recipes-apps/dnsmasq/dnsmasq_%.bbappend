SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://dnsmasq.conf "

do_install_append() {
	install -m 0444 ${WORKDIR}/dnsmasq.conf ${D}${sysconfdir}/
}




SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://dnsmasq.conf \
            file://dnsmasq.service "

do_install:append() {
	install -m 0444 ${WORKDIR}/dnsmasq.conf ${D}${sysconfdir}/
	install -m 0444 ${WORKDIR}/dnsmasq.service ${D}/lib/systemd/system/
}




SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://bluetooth.service \
            file://simple-agent"

do_install:append () {
    install -m 0644 ${WORKDIR}/bluetooth.service ${D}${base_libdir}/systemd/system/
    install -m 0755 ${WORKDIR}/simple-agent ${D}${libdir}/bluez/test/
}


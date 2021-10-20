SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://interfaces"

do_install:append () {
    install -m 0644 ${WORKDIR}/interfaces ${D}${sysconfdir}/network/interfaces
}


SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://sudoers"

do_install_append () {
    install -m 0644 ${WORKDIR}/sudoers ${D}${sysconfdir}/sudoers
}


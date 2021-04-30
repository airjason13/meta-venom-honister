SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://connman-applet.desktop"

do_install_append () {
    install -m 0644 ${WORKDIR}/connman-applet.desktop ${D}${sysconfdir}/xdg/autostart/
}


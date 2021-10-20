SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
#SRC_URI += "file://connman-applet.desktop"

do_install:prepend() {
       mkdir -p ${D}/usr/share/icons/hicolor/128x128/apps
       mkdir -p ${D}/usr/share/icons/hicolor/48x48/apps
       mkdir -p ${D}/usr/share/icons/hicolor/16x16/apps
       mkdir -p ${D}/usr/share/icons/hicolor/scalable/apps
}




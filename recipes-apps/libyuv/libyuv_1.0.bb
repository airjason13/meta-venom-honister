SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://libyuv \
            file://LICENSE "

S = "${WORKDIR}/libyuv"

inherit pkgconfig cmake

INSANE_SKIP:${PN} = "ldflags"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://compat/ \
            file://libs/ \
            file://include/ \
            file://Makefile \
            file://config.h \
            file://LICENSE "

S = "${WORKDIR}"

do_compile() {
	make 
}

do_install() {
    install -d ${D}/${bindir}
    install -m 755 prog/ledclient ${D}/${bindir}
}

DEPENDS += "ffmpeg libsdl2"
INSANE_SKIP_${PN} = "ldflags"

INSANE_SKIP_${PN}-dev = "ldflags"

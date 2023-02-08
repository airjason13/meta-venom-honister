SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://libs/ \
            file://utildbglib \
            file://Makefile \
            file://config.h \
            file://LICENSE "

S = "${WORKDIR}"

do_compile() {
	make 
}

do_install() {
    install -d ${D}/${bindir}
    install -m 755 prog/fftrans ${D}/${bindir}
}



DEPENDS += "ffmpeg libsdl2 libusb1 "
RDEPENDS:${PN} += "libubootenv ffmpeg libsdl2 "
RDEPENDS:${PN} += "python3-core"
RDEPENDS:${PN} += "python-core"
INSANE_SKIP:${PN} = "ldflags"


INSANE_SKIP:${PN}-dev = "ldflags"

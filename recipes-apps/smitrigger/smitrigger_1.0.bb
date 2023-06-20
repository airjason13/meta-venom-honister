SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://compat/ \
            file://libs/ \
            file://utildbglib \
            file://lcdclilib \
            file://jtimerlib \
            file://smilib \
            file://include/ \
            file://Makefile \
            file://config.h \
            file://test_diming.py \
            file://LICENSE "

S = "${WORKDIR}"

do_compile() {
	make 
}

do_install() {
    install -d ${D}/${bindir}
    install -m 755 prog/smi_trigger ${D}/${bindir}
    install -m 755 test_diming.py ${D}/${bindir}
}

RDEPENDS:${PN} += "python3-core"
RDEPENDS:${PN} += "python-core"
INSANE_SKIP:${PN} = "ldflags"


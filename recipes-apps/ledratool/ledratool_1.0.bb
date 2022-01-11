SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://pyLedRATool/ \
            file://launch_pyLedRATool.sh \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/${sysconfdir}
    install -d ${D}/home/root/pyLedRATool/
    install -m 755 launch_pyLedRATool.sh ${D}/${bindir}
    cp -r pyLedRATool/* ${D}/home/root/pyLedRATool/
}

FILES:${PN} += " \
                /home/root/* \
                "

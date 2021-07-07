SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://pyLedServer/ \
            file://launch_pyLedServer.sh \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/${sysconfdir}
    install -d ${D}/home/root/pyLedServer/
    install -m 755 launch_pyLedServer.sh ${D}/${bindir}
    cp -r pyLedServer/* ${D}/home/root/pyLedServer/
}



FILES_${PN} += " \
                /home/root/* \
                "

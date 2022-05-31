SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"

SRC_URI += "file://pyLedTester/ \
            file://launch_pyLedTester.sh \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/${sysconfdir}
    install -d ${D}/home/root/pyLedTester/
    install -m 755 launch_pyLedTester.sh ${D}/${bindir}
    cp -r pyLedTester/* ${D}/home/root/pyLedTester/
}



FILES:${PN} += " \
                /home/root/* \
                "

SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://pyqt5_led_player/ \
            file://Demo_Video/ \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/home/root/pyqt5_led_player/
    install -d ${D}/home/root/Videos/Demo_Video/
    cp -r Demo_Video/* ${D}/home/root/Videos/Demo_Video/
    cp -r pyqt5_led_player/* ${D}/home/root/pyqt5_led_player/

}



FILES:${PN} += " \
                /home/root/* \
                "

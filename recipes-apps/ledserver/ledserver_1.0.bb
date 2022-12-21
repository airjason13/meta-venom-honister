SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://pyLed_Server/ \
            file://pyzmq_server_rep/ \
            file://launch_pyLedServer.sh \
            file://msjhbd.ttc \
            file://subtitle_blank.jpg \
            file://subtitle.dat \
            file://subtitle_size.dat \
            file://subtitle_speed.dat \
            file://subtitle_position.dat \
            file://subtitle_period.dat \
            file://demo_videos/ \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/${sysconfdir}
    install -d ${D}/home/root/pyLedServer/
    install -d ${D}/home/root/pyzmq_server_rep/
    install -d ${D}/home/root/Videos/fonts/
    install -d ${D}/home/root/Videos/.subtitle_data
    install -m 755 launch_pyLedServer.sh ${D}/${bindir}
    cp -r pyLed_Server/* ${D}/home/root/pyLedServer/
    cp -r pyzmq_server_rep/* ${D}/home/root/pyzmq_server_rep/
    cp -r msjhbd.ttc ${D}/home/root/Videos/fonts/
    cp -r demo_videos/* ${D}/home/root/Videos/
    cp -r subtitle.dat ${D}/home/root/Videos/.subtitle_data/
    cp -r subtitle_size.dat ${D}/home/root/Videos/.subtitle_data/
    cp -r subtitle_period.dat ${D}/home/root/Videos/.subtitle_data/
    cp -r subtitle_speed.dat ${D}/home/root/Videos/.subtitle_data/
    cp -r subtitle_position.dat ${D}/home/root/Videos/.subtitle_data/
    cp -r subtitle_blank.jpg ${D}/home/root/Videos/.subtitle_data/

}
pkg_postinst_${PN} () {
       chmod 777 /home/root/
}




FILES:${PN} += " \
                /home/root/* \
                "

RDEPENDS:${PN} += "python3-core"

SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://flask-filemanager/ \
            file://launch_flask-filemanager.sh \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/home/root/flask-filemanager/
    install -m 755 launch_flask-filemanager.sh ${D}/${bindir}
    cp -r flask-filemanager/* ${D}/home/root/flask-filemanager/

}
pkg_postinst_${PN} () {
       chmod 777 /home/root/
}


RDEPENDS:${PN} = "perl"

FILES:${PN} += " \
                /home/root/* \
                "

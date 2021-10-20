SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://Richfilemanager/ \
			file://run-filemanager.sh \
			file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/home/root/RichFilemanager-Python3Flask/
    install -m 755 run-filemanager.sh ${D}/${bindir}
    cp -r Richfilemanager/* ${D}/home/root/RichFilemanager-Python3Flask/
}



FILES_${PN} += " \
                /home/root/* \
                "

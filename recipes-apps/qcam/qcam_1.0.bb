SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://files/qcam \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}${bindir}
    install -m 755 ${S}/files/qcam ${D}${bindir}
}

RDEPENDS:${PN} = "\
          qtbase \
          qtmultimedia \
          tiff \
          jlibcamera \
         "


FILES:${PN} += " \
		${bindir} \
                "


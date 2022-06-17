SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://files/libtensorflowlite.so \
            file://files/libtensorflow-lite.so \
            file://files/libtensorflowlite_c.so \
            file://files/tensorflow.pc \
            file://files/tensorflow-lite.pc \
            file://files/detect.tflite \
            file://files/labelmap.txt \
            file://files/object_detect_tf.json \
            file://files/tensorflow/ \
            file://LICENSE \
             "

S = "${WORKDIR}"

do_install() {
    install -d ${D}${libdir}
    install -d ${D}${libdir}/pkgconfig
    install -d ${D}${includedir}/tensorflow
    install -d ${D}${datadir}/tflite
    cp -r ${S}/files/libtensorflowlite.so ${D}${libdir}
    cp -r ${S}/files/libtensorflow-lite.so ${D}${libdir}
    cp -r ${S}/files/libtensorflowlite_c.so ${D}${libdir}
    cp -r ${S}/files/detect.tflite ${D}${datadir}/tflite
    cp -r ${S}/files/labelmap.txt ${D}${datadir}/tflite
    cp -r ${S}/files/object_detect_tf.json ${D}${datadir}/tflite
    cp -r ${S}/files/tensorflow.pc ${D}${libdir}/pkgconfig/
    cp -r ${S}/files/tensorflow-lite.pc ${D}${libdir}/pkgconfig/
    cp -r ${S}/files/tensorflow/* ${D}${includedir}/tensorflow/
}

FILES:${PN} += " \
                /usr/lib/ \
                /usr/include/ \
                /usr/share/ \
                "
INSANE_SKIP:${PN} += " ldflags"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "already-stripped"

#FILES:${PN}-dev += " \
#                /usr/lib/libtensorflowlite.so \
#                /usr/lib/libtensorflowlite_c.so \
#                "
#INSANE:SKIP_${PN}-dev += "dev-elf"

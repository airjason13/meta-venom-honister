SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://py-dep-whl/ \
            file://LICENSE \
             "
inherit python3-dir

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/cv2
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/opencv_python-3.4.11.43.dist-info
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/ffmpy-0.3.0-py3.9.egg-info


    cp -r ${S}/py-dep-whl/opencv-python/cv2/* ${D}${libdir}/${PYTHON_DIR}/site-packages/cv2/
    cp -r ${S}/py-dep-whl/opencv-python/opencv_python-3.4.11.43.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/opencv_python-3.4.11.43.dist-info/

    cp -r ${S}/py-dep-whl/ffmpy/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    cp -r ${S}/py-dep-whl/netifaces/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    cp -r ${S}/py-dep-whl/pynput/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    cp -r ${S}/py-dep-whl/evdev/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    cp -r ${S}/py-dep-whl/python-xlib/* ${D}${libdir}/${PYTHON_DIR}/site-packages/

}



FILES_${PN} += " \
                ${libdir}/${PYTHON_DIR}/site-packages/* \
                "

DEPENDS += " \
            ffmpeg \
            zlib \
            gstreamer1.0 \
            gstreamer1.0-plugins-base \
            libwebp \
            tiff \
           "

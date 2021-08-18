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
	#cv2
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/cv2
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/opencv_python-3.4.11.43.dist-info
	#ffmpy
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/ffmpy-0.3.0-py3.9.egg-info
	#pyqtgraph
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph-0.12.2.dist-info
	#qdarkstyle
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/qdarkstyle

	#requests
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/requests
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/requests-2.26.0.dist-info
	
	#pyudev
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev-0.22.0-py3.9.egg-info



    cp -r ${S}/py-dep-whl/opencv-python/cv2/* ${D}${libdir}/${PYTHON_DIR}/site-packages/cv2/
    cp -r ${S}/py-dep-whl/opencv-python/opencv_python-3.4.11.43.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/opencv_python-3.4.11.43.dist-info/

	cp -r ${S}/py-dep-whl/pyqtgraph/pyqtgraph/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph/
	cp -r ${S}/py-dep-whl/pyqtgraph/pyqtgraph-0.12.2.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph-0.12.2.dist-info/
	
	cp -r ${S}/py-dep-whl/qdarkstyle/qdarkstyle/* ${D}${libdir}/${PYTHON_DIR}/site-packages/qdarkstyle/

	#cp -r ${S}/py-dep-whl/requests/requests/* ${D}${libdir}/${PYTHON_DIR}/site-packages/requests
	#cp -r ${S}/py-dep-whl/requests/requests-2.26.0.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/requests-2.26.0.dist-info/

	#cp -r ${S}/py-dep-whl/pyudev/pyudev/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev/
	#cp -r ${S}/py-dep-whl/pyudev/pyudev-0.22.0-py3.9.egg-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev-0.22.0-py3.9.egg-info/
	

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

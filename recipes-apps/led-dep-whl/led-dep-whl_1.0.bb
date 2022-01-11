SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
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
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph-0.12.3.dist-info
    #qdarkstyle
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/qdarkstyle

    #requests
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/requests
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/requests-2.26.0.dist-info
	
    #pyudev
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev-0.22.0-py3.9.egg-info
	
    #udiskie
    install -d ${D}/${bindir}
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/udiskie
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/udiskie-2.3.3.dist-info
	
    #docopt
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/docopt-0.6.2-py3.9.egg-info

    #PIL
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/Pillow-8.3.2.dist-info
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/Pillow.libs
    #install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/PIL

    #qtpy
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/qtpy

    #qtmodern
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/qtmodern
    install -d ${D}${libdir}/${PYTHON_DIR}/site-packages/qtmodern-0.2.0.dist-info

    cp -r ${S}/py-dep-whl/opencv-python/cv2/* ${D}${libdir}/${PYTHON_DIR}/site-packages/cv2/
    cp -r ${S}/py-dep-whl/opencv-python/opencv_python-3.4.11.43.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/opencv_python-3.4.11.43.dist-info/

    cp -r ${S}/py-dep-whl/pyqtgraph/pyqtgraph/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph/
    cp -r ${S}/py-dep-whl/pyqtgraph/pyqtgraph-0.12.3.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyqtgraph-0.12.3.dist-info/
	
    cp -r ${S}/py-dep-whl/qdarkstyle/qdarkstyle/* ${D}${libdir}/${PYTHON_DIR}/site-packages/qdarkstyle/

    #cp -r ${S}/py-dep-whl/requests/requests/* ${D}${libdir}/${PYTHON_DIR}/site-packages/requests
    #cp -r ${S}/py-dep-whl/requests/requests-2.26.0.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/requests-2.26.0.dist-info/

    #cp -r ${S}/py-dep-whl/pyudev/pyudev/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev/
    #cp -r ${S}/py-dep-whl/pyudev/pyudev-0.22.0-py3.9.egg-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/pyudev-0.22.0-py3.9.egg-info/
	

    cp -r ${S}/py-dep-whl/ffmpy/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    #cp -r ${S}/py-dep-whl/netifaces/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    cp -r ${S}/py-dep-whl/pynput/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    #cp -r ${S}/py-dep-whl/evdev/* ${D}${libdir}/${PYTHON_DIR}/site-packages/
    
    #python-xlib
    cp -r ${S}/py-dep-whl/python-xlib/* ${D}${libdir}/${PYTHON_DIR}/site-packages/

    #udiskie
    cp -r ${S}/py-dep-whl/udiskie/udiskie/* ${D}${libdir}/${PYTHON_DIR}/site-packages/udiskie/
    cp -r ${S}/py-dep-whl/udiskie/udiskie-2.3.3.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/udiskie-2.3.3.dist-info/
    install -m 755 ${S}/py-dep-whl/udiskie/usr_bin/* ${D}/${bindir}/
    
    #qtmodern
    cp -r ${S}/py-dep-whl/qtmodern/qtmodern/* ${D}${libdir}/${PYTHON_DIR}/site-packages/qtmodern/
    cp -r ${S}/py-dep-whl/qtmodern/qtmodern-0.2.0.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/qtmodern-0.2.0.dist-info/
	
    #docopt
    #cp -r ${S}/py-dep-whl/docopt/docopt.py ${D}${libdir}/${PYTHON_DIR}/site-packages/
    #cp -r ${S}/py-dep-whl/docopt/docopt-0.6.2-py3.9.egg-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/docopt-0.6.2-py3.9.egg-info/

    #PIL
    #cp -r ${S}/py-dep-whl/PIL/Pillow-8.3.2.dist-info/* ${D}${libdir}/${PYTHON_DIR}/site-packages/Pillow-8.3.2.dist-info/
    #cp -r ${S}/py-dep-whl/PIL/PIL/* ${D}${libdir}/${PYTHON_DIR}/site-packages/PIL/
    #cp -r ${S}/py-dep-whl/PIL/Pillow.libs/* ${D}${libdir}/${PYTHON_DIR}/site-packages/Pillow.libs

    #qtpy
    cp -r ${S}/py-dep-whl/qtpy/qtpy/* ${D}${libdir}/${PYTHON_DIR}/site-packages/qtpy/

}



FILES:${PN} += " \
                ${libdir}/${PYTHON_DIR}/site-packages/* \
		${bindir} \
                "

DEPENDS += " \
            ffmpeg \
            zlib \
            gstreamer1.0 \
            gstreamer1.0-plugins-base \
            libwebp \
            tiff \
			python3 \
           "
RDEPENDS:${PN} = "\
		  python3-core \
   		  gtk+3 \
   		  libdc1394 \
   		  gdk-pixbuf \
   		  atk \
		 "
INSANE:SKIP_${PN}:append = "already-stripped"

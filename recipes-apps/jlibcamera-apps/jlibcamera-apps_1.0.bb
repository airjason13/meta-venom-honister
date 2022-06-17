SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE="CLOSED"
#SRC_URI = "https://github.com/raspberrypi/libcamera-apps;protocol=file;branch=master"

SRC_URI = "https://github.com/raspberrypi/libcamera-apps/archive/refs/heads/main.zip;protocol=http"

#SRCREV = "6582a730b059f086552414b034c90688cca047eb"
SRC_URI[sha256sum] = "2b3375c841248df8c8a7f66636fbddfc572bfba0dc45251b0f346694d1035ab8"

S = "${WORKDIR}/libcamera-apps-main"
#B = "${WORKDIR}/build"

inherit cmake pkgconfig

EXTRA_OECMAKE = "-DENABLE_DRM=1 -DENABLE_X11=1 -DENABLE_QT=1 -DENABLE_OPENCV=1 -DENABLE_TFLITE=1"




FILES:${PN} += " \
		${bindir} \
		/usr/lib/ \
		/usr/share/ \
                "

#FILES:${PN}-dev += " ${libdir}/libpreview.so"
#FILES:${PN}-dev += " ${libdir}/libimage.so"

DEPENDS += "\
          python3 \
          boost \
          libexif \
          libepoxy \
          jlibcamera \
          libdrm \
          libevent \
          libsdl2 \
          libyaml \
          qtbase \
          gstreamer1.0 \
          elfutils \
          libunwind \
          gstreamer1.0-plugins-base \
          tiff \
          tf-lite \
          flatbuffers \
          opencv \
                "

RDEPENDS:${PN} = "\
          python3-core \
          jlibcamera \
          libepoxy \
          libexif \
          boost \
          libdrm \
          libevent \
          libsdl2 \
          libyaml \
          qtbase \
          gstreamer1.0 \
          elfutils \
          libunwind \
          gstreamer1.0-plugins-base \
          tiff \
          tf-lite \
          flatbuffers \
          opencv \  
         "

INSANE_SKIP_${PN} += " ldflags"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""
INSANE:SKIP_${PN}:append = "already-stripped"

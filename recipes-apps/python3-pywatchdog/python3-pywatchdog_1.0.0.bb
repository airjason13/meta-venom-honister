
SUMMARY = "Interact with a Linux watchdog driver using Python."
HOMEPAGE = "https://github.com/AT0myks/pywatchdog"
AUTHOR = "AT0myks <at0myks.dev@gmail.com>"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=242f4efed30b921ee5901df2eeedbb21"

SRC_URI = "https://files.pythonhosted.org/packages/be/e0/b716b24294e7517d615cd9bd2fb0d038e12eccf44ad332c91b9f5e2e714d/pywatchdog-1.0.0.tar.gz"
SRC_URI[md5sum] = "93d3f8a67ec5deea53643656a0fa9da9"
SRC_URI[sha256sum] = "94bb6bd52faba69e0e278e5c5f8e68560961cddae8640cf9af4680de3dda52dd"

S = "${WORKDIR}/pywatchdog-1.0.0"

RDEPENDS_${PN} = ""

inherit setuptools3

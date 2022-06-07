
SUMMARY = "Scientific Graphics and GUI Library for Python"
HOMEPAGE = "http://www.pyqtgraph.org"
AUTHOR = "Luke Campagnola <luke.campagnola@gmail.com>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=f3e5f0e3bfada0ee09266e5402b0a690"

SRC_URI = "https://files.pythonhosted.org/packages/76/b8/06b2ce771794639f5fa82bff9e5859d9dc5ca3e5e1639c0af52728c9f6f1/pyqtgraph-0.12.4.tar.gz"
SRC_URI[md5sum] = "adc6e3c9148f5999ffbe05e7431899b0"
SRC_URI[sha256sum] = "c2c8f2b7e1d7f97a710f370acff6368d686c9d6cdc560f2d83dcf59185dfa19d"

S = "${WORKDIR}/pyqtgraph-0.12.4"

RDEPENDS_${PN} = "python3-numpy"

inherit setuptools3

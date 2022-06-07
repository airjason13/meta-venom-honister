
SUMMARY = "Provides an abstraction layer on top of the various Qt bindings (PyQt5/6 and PySide2/6)."
HOMEPAGE = "https://github.com/spyder-ide/qtpy"
AUTHOR = "Colin Duquesnoy and the Spyder Development Team <spyder.python@gmail.com>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=b2830f54500be1314b9ec6096989f983"

SRC_URI = "https://files.pythonhosted.org/packages/4f/8b/2830a11f0773dded3bb9943daeed7c1eefb214f84d72a213a5d4681430b2/QtPy-2.1.0.tar.gz"
SRC_URI[md5sum] = "cfeeb8e33c3aca5adfabe08627581ab0"
SRC_URI[sha256sum] = "ca8cd4217175186344299ee4c0f7e7adcf362c70852ba35b255a534077025c06"

S = "${WORKDIR}/QtPy-2.1.0"

RDEPENDS_${PN} = "python3-packaging"

inherit setuptools3

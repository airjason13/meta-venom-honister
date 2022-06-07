
SUMMARY = "The most complete dark/light style sheet for C++/Python and Qt applications"
HOMEPAGE = "https://github.com/ColinDuquesnoy/QDarkStyleSheet"
AUTHOR = "Colin Duquesnoy <colin.duquesnoy@gmail.com>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.rst;md5=78017f23d8a398e7fca5b6a757601ca2"

SRC_URI = "https://files.pythonhosted.org/packages/1a/1c/00ca31b13727ade22d1b42b61dc86056493a72f01912082a61cb34e5abf6/QDarkStyle-3.1.tar.gz"
SRC_URI[md5sum] = "1f98ffafdce2a44b3398db40c8c8ed1c"
SRC_URI[sha256sum] = "600584d625343e0ddd128de08393d3c35637786a49827f174d29aa7caa8279c1"

S = "${WORKDIR}/QDarkStyle-3.1"

RDEPENDS_${PN} = "python3-qtpy"

inherit setuptools3


SUMMARY = "A libudev binding"
HOMEPAGE = "http://pyudev.readthedocs.org/"
AUTHOR = "Sebastian Wiesner <lunaryorn@gmail.com>"
LICENSE = "LGPL 2.1+"
LIC_FILES_CHKSUM = "file://COPYING;md5=a6f89e2100d9b6cdffcea4f398e37343"

SRC_URI = "https://files.pythonhosted.org/packages/f8/fa/ae6c1a1a75f19560bbd875a579b2ca9b32deeae6a4c4a1997f4ec69a013e/pyudev-0.23.2.tar.gz"
SRC_URI[md5sum] = "903ce95dc8dd787014f224e2674e406f"
SRC_URI[sha256sum] = "32ae3585b320a51bc283e0a04000fd8a25599edb44541e2f5034f6afee5d15cc"

S = "${WORKDIR}/pyudev-0.23.2"

RDEPENDS_${PN} = "python3-six"

inherit setuptools3

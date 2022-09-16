
SUMMARY = "Calculations for the position of the sun and moon."
HOMEPAGE = "https://github.com/sffjunkie/astral"
AUTHOR = "Simon Kennedy <sffjunkie+code@gmail.com>"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2a944942e1496af1886903d274dedb13"

SRC_URI = "https://files.pythonhosted.org/packages/ad/c3/76dfe55a68c48a1a6f3d2eeab2793ebffa9db8adfba82774a7e0f5f43980/astral-2.2.tar.gz"
SRC_URI[md5sum] = "4b7f144a2d0f743295ebe97de08406de"
SRC_URI[sha256sum] = "e41d9967d5c48be421346552f0f4dedad43ff39a83574f5ff2ad32b6627b6fbe"

S = "${WORKDIR}/astral-2.2"

RDEPENDS_${PN} = "python3-pytz"

inherit setuptools3

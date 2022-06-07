
SUMMARY = "Qt Widgets Modern User Interface"
HOMEPAGE = "https://www.github.com/gmarull/qtmodern"
AUTHOR = "Gerard Marull-Paretas <gerardmarull@gmail.com>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=65173ef7762f5c829d19b766b984346b"

SRC_URI = "https://files.pythonhosted.org/packages/e3/17/bc8a3882571e852e96d79b8c5a6989f72e2b7eda22998cd6018bfc5644fb/qtmodern-0.2.0.tar.gz"
SRC_URI[md5sum] = "d2dd8af8ab4d110cbb72d705a76a9f36"
SRC_URI[sha256sum] = "d433a54fbb400d49790aff65d35f203de2a8cc67795ac5bb04c5e766433fafae"

S = "${WORKDIR}/qtmodern-0.2.0"

RDEPENDS_${PN} = "python3-qtpy"

inherit setuptools3

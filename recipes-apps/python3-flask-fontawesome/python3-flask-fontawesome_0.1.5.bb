
SUMMARY = "FontAwesome for Flask"
HOMEPAGE = "https://github.com/heartsucker/flask-fontawesome"
AUTHOR = "heartsucker <heartsucker@autistici.org>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-APACHE;md5=3fb10703a2aadfdc3d3c24143723a705"

SRC_URI = "https://files.pythonhosted.org/packages/87/40/d5780675fa8bec026a26cafcb4e9f31eec60d878896dee42ee7cda8f35cd/Flask-FontAwesome-0.1.5.tar.gz"
SRC_URI[md5sum] = "75cee6ec39c15ad514f0f0651e17254c"
SRC_URI[sha256sum] = "1279c6c00e6cfebd086d1df0a7a6c6c59b44f636805521dbe640561aeb8c79a0"

S = "${WORKDIR}/Flask-FontAwesome-0.1.5"

RDEPENDS_${PN} = "python3-flask"

inherit setuptools3

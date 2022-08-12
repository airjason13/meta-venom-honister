
SUMMARY = "A concise Flask extension to render QR codes on Jinja2 templates using python-qrcode"
HOMEPAGE = "https://github.com/marcoagner/Flask-QRcode"
AUTHOR = "Marco Agner <marco@agner.io>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=3c34afdc3adf82d2448f12715a255122"

SRC_URI = "https://files.pythonhosted.org/packages/6f/2a/69e9ec20a6215ec5ea0c8346f65cd249537e3e72ce34414be61d39f9b83c/Flask-QRcode-3.1.0.tar.gz"
SRC_URI[md5sum] = "128830e4f5d12d388458dbb74b79c7f2"
SRC_URI[sha256sum] = "2b0598c9ebc67f3f9ca18fb1ee64b365a4c76ab528bd9e1dc69a71d590e98a78"

S = "${WORKDIR}/Flask-QRcode-3.1.0"

RDEPENDS_${PN} = "python3-flask python3-qrcode python3-pillow"

inherit setuptools3

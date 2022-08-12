
SUMMARY = "QR Code image generator"
HOMEPAGE = "https://github.com/lincolnloop/python-qrcode"
AUTHOR = "Lincoln Loop <info@lincolnloop.com>"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://LICENSE;md5=4b802d2a65df4626623c79757f486af9"

SRC_URI = "https://files.pythonhosted.org/packages/94/9f/31f33cdf3cf8f98e64c42582fb82f39ca718264df61957f28b0bbb09b134/qrcode-7.3.1.tar.gz"
SRC_URI[md5sum] = "124103c685e96ba3b7a1616760f31c11"
SRC_URI[sha256sum] = "375a6ff240ca9bd41adc070428b5dfc1dcfbb0f2507f1ac848f6cded38956578"

S = "${WORKDIR}/qrcode-7.3.1"

RDEPENDS_${PN} = ""

inherit setuptools3

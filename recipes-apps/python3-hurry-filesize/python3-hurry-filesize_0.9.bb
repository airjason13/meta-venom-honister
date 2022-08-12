
SUMMARY = "A simple Python library for human readable file sizes (or anything sized in bytes)."
HOMEPAGE = "UNKNOWN"
AUTHOR = "Martijn Faassen, Startifact <faassen@startifact.com>"
LICENSE = "ZPL-2.0"
LIC_FILES_CHKSUM = "file://setup.py;md5=a46e50609ad2f6038c98b9ddb86221ee"

SRC_URI = "https://files.pythonhosted.org/packages/ee/5e/16e17bedcf54d5b618dc0771690deda77178e5c310402881c3d2d6c5f27c/hurry.filesize-0.9.tar.gz"
SRC_URI[md5sum] = "8549ccd09bb31b5ff1e8e8c1eacc7794"
SRC_URI[sha256sum] = "f5368329adbef86accd3bc9490522340bb79260455ae89b1a42c10f63801b9a6"

S = "${WORKDIR}/hurry.filesize-0.9"

RDEPENDS_${PN} = ""

inherit setuptools3

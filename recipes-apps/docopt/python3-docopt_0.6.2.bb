
SUMMARY = "Pythonic argument parser, that will make you smile"
HOMEPAGE = "http://docopt.org"
AUTHOR = "Vladimir Keleshev <vladimir@keleshev.com>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-MIT;md5=09b77fb74986791a3d4a0e746a37d88f"

SRC_URI = "https://files.pythonhosted.org/packages/a2/55/8f8cab2afd404cf578136ef2cc5dfb50baa1761b68c9da1fb1e4eed343c9/docopt-0.6.2.tar.gz"
SRC_URI[md5sum] = "4bc74561b37fad5d3e7d037f82a4c3b1"
SRC_URI[sha256sum] = "49b3a825280bd66b3aa83585ef59c4a8c82f2c8a522dbe754a8bc8d08c85c491"

S = "${WORKDIR}/docopt-0.6.2"

RDEPENDS_${PN} = ""

inherit setuptools3

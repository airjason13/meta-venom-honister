
SUMMARY = "Removable disk automounter for udisks"
HOMEPAGE = "https://github.com/coldfix/udiskie"
AUTHOR = "Byron Clark <byron@theclarkfamily.name>"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYING;md5=f7d6dd19680ac1c4995e76442b897458"

SRC_URI = "https://files.pythonhosted.org/packages/86/11/b03d85f92a244899158f93eb562c91d44e0f2422954f1c4ba3a3dada58b5/udiskie-2.4.2.tar.gz"
SRC_URI[md5sum] = "cec25c498f66251562936a3862cdf54e"
SRC_URI[sha256sum] = "1f87ab59cb112915be044fc2ae0b0000a48189af54353793b896ec6c289a0f7c"

S = "${WORKDIR}/udiskie-2.4.2"
# DEPENDS += "gettext-native"
RDEPENDS_${PN} = "python3-pyyaml python3-docopt python3-pygobject"

inherit setuptools3 gettext

FILES:${PN} += " /usr/share/zsh/ \
                /usr/share/zsh/site-functions/ \
                "


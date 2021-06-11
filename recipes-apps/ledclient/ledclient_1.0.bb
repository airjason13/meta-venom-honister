SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://Makefile \
            file://LICENSE "

S = "${WORKDIR}"

do_compile() {
	make 
}


DEPENDS += "ffmpeg"

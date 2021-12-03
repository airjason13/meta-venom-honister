SUMMARY = "bitbake-layers recipe of ccrypt"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://ccrypt \
            file://LICENSE \
            "
             

S = "${WORKDIR}"

do_configure() {
    cd ccrypt
    ${S}/ccrypt/configure --host=aarch64 
}

do_compile() {
    cd ccrypt
    make
}

do_install() {
}




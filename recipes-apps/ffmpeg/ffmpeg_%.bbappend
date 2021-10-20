SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"


#add by Jason for test
DEPENDS += "libwebp"
DEPENDS += "zeromq"

#add by Jason for test
PACKAGECONFIG[libwebp] = "--enable-libwebp,--disable-libwebp,libwebp"
PACKAGECONFIG[libzmq] = "--enable-libzmq,--disable-libzmq,zeromq"





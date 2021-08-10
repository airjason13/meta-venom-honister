SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"


#add by Jason for test
DEPENDS += "libwebp"

#add by Jason for test
PACKAGECONFIG[libwebp] = "--enable-libwebp,--disble-libwebp,libwebp"


do_compile_append() {
	make examples
}




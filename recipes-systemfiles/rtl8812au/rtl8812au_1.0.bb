SUMMARY = "rtl8812au wifi module"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
SRC_URI = " \
		file://88XXau.ko \	
		file://LICENSE \	
	"


do_install() {
	install -d ${D}/home/root/rtl8812au_module/
	cp ${WORKDIR}/88XXau.ko ${D}/home/root/rtl8812au_module/
}

FILES:${PN} = " \
  /home/root/* \
  "


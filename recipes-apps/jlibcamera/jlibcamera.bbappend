PACKAGECONFIG[raspberrypi] = "-Dpipelines=raspberrypi"
PACKAGECONFIG:append:rpi = " raspberrypi"

#SRC_URI += "file://files/ \
#             file://LICENSE \
#            "

#S = "${WORKDIR}"

#do_install:append() {
#    install -d ${D}${bindir}
#    install -m 755 ${S}/files/qcam ${D}/${bindir}
#}

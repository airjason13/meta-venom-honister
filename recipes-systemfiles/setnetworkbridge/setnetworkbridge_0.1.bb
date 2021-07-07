SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "CLOSED"

SRC_URI += "file://set_br.sh \
            file://set_br.desktop \
            "

do_install () {
    mkdir -p ${D}${bindir}
    mkdir -p ${D}${sysconfdir}/xdg/autostart/
    install -m 755 ${WORKDIR}/set_br.sh ${D}${bindir}/set_br.sh
    #install -m 755 ${WORKDIR}/set_br.desktop ${D}${sysconfdir}/xdg/autostart/set_br.desktop
}

FILE_${PN} += "${bindir}/set_br.sh"



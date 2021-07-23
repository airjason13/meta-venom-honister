SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://compat/ \
            file://libs/ \
            file://ext/ \
            file://picousblib \
            file://udpmrlib \
            file://utildbglib \
            file://include/ \
            file://Makefile \
            file://config.h \
            file://LICENSE "

S = "${WORKDIR}"

do_compile() {
	make 
}

do_install() {
    install -d ${D}/${bindir}
    install -d ${D}/${sysconfdir}
    install -d ${D}/${sysconfdir}/xdg/autostart/
    install -d ${D}/home/root/led_machine_option/
    install -d ${D}/home/root/led_machine_option/templates/
    install -m 755 prog/ledclient ${D}/${bindir}
    install -m 755 ext/hwrevision ${D}/${sysconfdir}/
    install -m 755 ext/launch_led_role_option.sh ${D}/${bindir}
    install -m 755 ext/set_led_env.sh ${D}/${bindir}
    install -m 755 ext/launch_led_player.sh ${D}/${bindir}
    install -m 755 ext/set_always_display_on.sh ${D}/${bindir}
    install -m 755 ext/set_automount.sh ${D}/${bindir}
    install -m 755 ext/set_panel_autohide.sh ${D}/${bindir}
    cp -r ext/pyflask_machine_option/* ${D}/home/root/led_machine_option/
    install -m 755 ext/led_role.conf ${D}/home/root/
    install -m 755 ext/led_role_option.desktop ${D}${sysconfdir}/xdg/autostart/led_role_option.desktop
    install -m 755 ext/set_led_env.desktop ${D}${sysconfdir}/xdg/autostart/set_led_env.desktop
    install -m 755 ext/set_panel_autohide.desktop ${D}${sysconfdir}/xdg/autostart/set_panel_autohide.desktop
    install -m 755 ext/set_automount.desktop ${D}${sysconfdir}/xdg/autostart/set_panel_automount.desktop
    install -m 755 ext/set_always_display_on.desktop ${D}${sysconfdir}/xdg/autostart/set_always_display_on.desktop
}

DEPENDS += "ffmpeg libsdl2 libusb1"
RDEPENDS_${PN} = "libubootenv"
INSANE_SKIP_${PN} = "ldflags"


INSANE_SKIP_${PN}-dev = "ldflags"
FILES_${PN} += " \
                /home/root/* \
                "

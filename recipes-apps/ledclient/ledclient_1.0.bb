SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=e4ac654ba9b61686c2dc854a1128a323"
FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"
SRC_URI += "file://app/ \
            file://compat/ \
            file://libs/ \
            file://ext/ \
            file://picousblib \
            file://udputilslib \
            file://utildbglib \
            file://lcdclilib \
            file://jtimerlib \
            file://cabinetutilslib \
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
    install -d ${D}/home/root/i2c_lcd_server/
    install -d ${D}/home/root/led_machine_option/
    install -d ${D}/home/root/led_machine_option/templates/
    install -d ${D}/home/root/.cabinets_params/
    install -m 755 prog/ledclient ${D}/${bindir}
    install -m 755 ext/hwrevision ${D}/${sysconfdir}/
    install -m 755 ext/launch_led_role_option.sh ${D}/${bindir}
    install -m 755 ext/set_led_env.sh ${D}/${bindir}
    install -m 755 ext/launch_led_player.sh ${D}/${bindir}
    install -m 755 ext/launch_i2c_lcd_server.sh ${D}/${bindir}
    install -m 755 ext/launch_led_client.sh ${D}/${bindir}
    install -m 755 ext/launch_led_aio_client.sh ${D}/${bindir}
    install -m 755 ext/set_always_display_on.sh ${D}/${bindir}
    install -m 755 ext/set_br.sh ${D}/${bindir}
    install -m 755 ext/set_automount.sh ${D}/${bindir}
    install -m 755 ext/set_panel_autohide.sh ${D}/${bindir}
    install -m 755 ext/setup_hotspot.sh ${D}/${bindir}
    install -m 755 ext/setup_hotspot_alfa.sh ${D}/${bindir}
    install -m 755 ext/configure_hotspot_alfa.sh ${D}/${bindir}
    install -m 755 ext/setup_hotspot_tester.sh ${D}/${bindir}
    install -m 755 ext/b_measure_temp.sh ${D}/${bindir}
    install -m 755 ext/ra_client.py ${D}/${bindir}
    install -m 755 ext/ra_zmq_send.py ${D}/${bindir}
    install -m 755 ext/write_tc358743_edid.sh ${D}/${bindir}
    install -m 755 ext/tc358743_edid.txt ${D}/${sysconfdir}/
    install -m 755 ext/check_client_peripheral_devices.sh ${D}/${bindir}
    install -m 755 ext/check_server_peripheral_devices.sh ${D}/${bindir}
    install -m 755 ext/probe_g_mass.sh ${D}/${bindir}
    install -m 755 ext/provision.sh ${D}/${bindir}
    install -m 755 ext/fdisk-mmcblk0p2.sh ${D}/${bindir}
    install -m 755 ext/bt_discoverable.sh ${D}/${bindir}
    install -m 755 ext/rfcomm-server-sdp.py ${D}/${bindir}
    install -m 755 ext/chromium.sh ${D}/${bindir}
    install -m 755 ext/speedup_chromium.sh ${D}/${bindir}
    install -m 755 ext/mount_piusb.sh ${D}/${bindir}
    install -m 755 ext/generate_machine_info.sh ${D}/${bindir}
    cp -r ext/piusb.bin ${D}/home/root/
    cp -r ext/pyflask_machine_option/* ${D}/home/root/led_machine_option/
    cp -r ext/py1602_server/* ${D}/home/root/i2c_lcd_server/
    cp -r ext/default_cabinets_params/.cabinet_params_config_* ${D}/home/root/.cabinets_params/
    install -m 755 ext/led_role.conf ${D}/home/root/
    install -m 755 ext/led_role_option.desktop ${D}${sysconfdir}/xdg/autostart/led_role_option.desktop
    install -m 755 ext/i2c_lcd.desktop ${D}${sysconfdir}/xdg/autostart/i2c_lcd.desktop
    install -m 755 ext/set_led_env.desktop ${D}${sysconfdir}/xdg/autostart/set_led_env.desktop
    install -m 755 ext/set_panel_autohide.desktop ${D}${sysconfdir}/xdg/autostart/set_panel_autohide.desktop
    install -m 755 ext/set_automount.desktop ${D}${sysconfdir}/xdg/autostart/set_panel_automount.desktop
    install -m 755 ext/set_always_display_on.desktop ${D}${sysconfdir}/xdg/autostart/set_always_display_on.desktop
    install -m 755 ext/provision.desktop ${D}${sysconfdir}/xdg/autostart/provision.desktop
    install -m 755 ext/probe_g_mass.desktop ${D}${sysconfdir}/xdg/autostart/probe_g_mass.desktop
    install -m 755 ext/mount_piusb.desktop ${D}${sysconfdir}/xdg/autostart/mount_piusb.desktop
    install -m 755 ext/swversion ${D}${sysconfdir}
    install -m 755 ext/gisled_default_connection ${D}${sysconfdir}
}

pkg_postinst_${PN} () {
       chmod 777 /home/root/
}


DEPENDS += "ffmpeg libsdl2 libusb1 "
RDEPENDS:${PN} += "libubootenv ffmpeg libsdl2 libusb1 "
RDEPENDS:${PN} += "python3-core"
RDEPENDS:${PN} += "python-core"
INSANE_SKIP:${PN} = "ldflags"


INSANE_SKIP:${PN}-dev = "ldflags"
FILES:${PN} += " \
                /home/root/* \
                /home/root/.cabinets_params/.cabinet_params_config_* \
                "

SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"

FILESEXTRAPATHS:append := "${THISDIR}/${PN}:"

do_deploy:append() {
    if [ -n "${FORCE_TURBO}" ]; then
        sed -i '/#force_turbo=/ c\force_turbo=${FORCE_TURBO}' ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/config.txt
    fi
    if [ "${TC358743}" = "1" ]; then
        echo "# Enable TC358743 HDMItoCSI" >>$CONFIG
        echo "dtoverlay=tc358743" >>$CONFIG
    fi
    if [ "${OV5647}" = "1" ]; then
        echo "# Enable OV5647 Image Sensor" >>$CONFIG
        echo "dtoverlay=ov5647" >>$CONFIG
    fi
    if [ "${IMX519}" = "1" ]; then
        echo "# Enable OVIMX519 Image Sensor" >>$CONFIG
        echo "dtoverlay=imx519" >>$CONFIG
    fi
    if [ "${I2C3}" = "1" ]; then
        echo "# Enable I2C3" >>$CONFIG
        echo "dtoverlay=i2c3" >>$CONFIG
    fi
    if [ "${I2C4}" = "1" ]; then
        echo "# Enable I2C4" >>$CONFIG
        echo "dtoverlay=i2c4" >>$CONFIG
    fi
    if [ "${I2C5}" = "1" ]; then
        echo "# Enable I2C5" >>$CONFIG
        echo "dtoverlay=i2c5" >>$CONFIG
    fi
    if [ "${I2C6}" = "1" ]; then
        echo "# Enable I2C6" >>$CONFIG
        echo "dtoverlay=i2c6" >>$CONFIG
    fi
    if [ "${DS3231}" = "1" ]; then
        echo "# Enable DS3231" >>$CONFIG
        echo "dtoverlay=i2c-rtc,ds3231" >>$CONFIG
    fi
    if [ "${DISABLE_TOUCHSCREEN}" = "1" ]; then
        echo "# Disable touch screen" >>$CONFIG
        echo "disable_touchscreen=1" >>$CONFIG
    fi
    if [ "${HDMI_SAFE}" = "1" ]; then
        echo "# Enable HDMI SAFE MODE" >>$CONFIG
        echo "hdmi_safe=1" >>$CONFIG
    fi
}

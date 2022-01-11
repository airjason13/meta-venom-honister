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
}

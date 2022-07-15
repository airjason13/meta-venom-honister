#!/bin/sh
PROVISION_FILE=/home/root/.provision

HOSTNAME_PREFIX=GIS_LED

if [ -f "$PROVISION_FILE" ];then
    
else
    fdisk-mmcblk0p2.sh
    sed -i '/raspberrypi4-64/ c\${HOSTNAME_PREFIX}' /etc/hostname    
    tuoch $PROVISION_FILE
fi


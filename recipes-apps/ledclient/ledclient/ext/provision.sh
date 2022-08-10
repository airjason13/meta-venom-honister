#!/bin/sh
PROVISION_FILE=/home/root/.provision

HOSTNAME_PREFIX=GIS_LED
if [ -f "$PROVISION_FILE" ];then
   echo "provisioned" 
else
    fdisk-mmcblk0p2.sh
    sed  -i "s|raspberrypi4-64|${HOSTNAME_PREFIX}|"   /etc/hostname    
    generate_machine_info.sh 
    timedatectl set-timezone Asia/Taipei #set Taipei timezone
	touch ${PROVISION_FILE}
    sync
    sync
    sync
    reboot
fi


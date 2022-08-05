#!/bin/sh
PROVISION_FILE=/home/root/.provision

HOSTNAME_PREFIX=GIS_LED
if [ -f "$PROVISION_FILE" ];then
   echo "provisioned" 
else
    fdisk-mmcblk0p2.sh
    #sed -i '/raspberrypi4-64/ c\${HOSTNAME_PREFIX}' /etc/hostname    
    sed  -i "s|raspberrypi4-64|${HOSTNAME_PREFIX}|"   /etc/hostname    
    generate_machine_info.sh
	touch ${PROVISION_FILE}
fi


#!/bin/sh
FILE=/etc/NetworkManager/system-connections/Hotspot.nmconnection
if [ -f "$FILE" ];then
	UUID=$(grep uuid $FILE | cut -d= -f2)
	echo UUID=$UUID
	nmcli con up uuid $UUID
else
    rm /etc/NetworkManager/system-connections/Hotspot-*.nmconnection
	nmcli con add type wifi ifname wlan0 con-name Hotspot autoconnect yes ssid LED-Pi-Server
	nmcli con modify Hotspot 802-11-wireless.mode ap 802-11-wireless.band a ipv4.method shared
	nmcli con modify Hotspot wifi-sec.key-mgmt wpa-psk
	nmcli con modify Hotspot wifi-sec.psk "12345678"
	nmcli con modify Hotspot ipv4.addresses 192.168.1.7/24
	nmcli con modify Hotspot ipv4.gateway 192.168.1.7
	nmcli con up Hotspot
fi

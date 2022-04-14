#!/bin/sh
ALFA_WIFI_ADAPTER=""
while true ; do
    if [ -f /sys/class/net/wlp1s0u1u1/address ];then
        echo "got alfa wifi adapter"
        ALFA_WIFI_ADAPTER="wlp1s0u1u1"
        break
    elif [ -f /sys/class/net/wlp1s0u1u2/address ];then
        echo "got alfa wifi adapter"
        ALFA_WIFI_ADAPTER="wlp1s0u1u2"
        break
    elif [ -f /sys/class/net/wlp1s0u1u3/address ];then
        echo "got alfa wifi adapter"
        ALFA_WIFI_ADAPTER="wlp1s0u1u3"
        break
    elif [ -f /sys/class/net/wlp1s0u1u4/address ];then
        echo "got alfa wifi adapter"
        ALFA_WIFI_ADAPTER="wlp1s0u1u4"
        break
    else
        echo "no alfa wifi adapter"  
        sleep 5
    fi
done
FILE=/etc/NetworkManager/system-connections/Hotspot_Alfa.nmconnection
MAC_ADDRESS=$(cat /sys/class/net/${ALFA_WIFI_ADAPTER}/address)
PREFIX="LED_Alfa"
SSID="${PREFIX}_${MAC_ADDRESS}"
if [ -f "$FILE" ];then
	UUID=$(grep uuid $FILE | cut -d= -f2)
	echo UUID=$UUID
	nmcli con up uuid $UUID
else
    rm /etc/NetworkManager/system-connections/Hotspot_Alfa*.nmconnection
	#nmcli con add type wifi ifname wlan0 con-name Hotspot autoconnect yes ssid LED-Pi-Server
	echo "SSID="$SSID
	nmcli con add type wifi ifname $ALFA_WIFI_ADAPTER con-name Hotspot_Alfa autoconnect yes ssid $SSID
	nmcli con modify Hotspot_Alfa 802-11-wireless.mode ap 802-11-wireless.band a ipv4.method shared
	nmcli con modify Hotspot_Alfa wifi-sec.key-mgmt wpa-psk
	nmcli con modify Hotspot_Alfa wifi-sec.psk "12345678"
	nmcli con modify Hotspot_Alfa ipv4.addresses 192.168.1.9/24
	nmcli con modify Hotspot_Alfa ipv4.gateway 192.168.1.9
	nmcli con up Hotspot_Alfa
fi

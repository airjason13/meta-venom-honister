#!/bin/sh

cpu_sn_p_file='/tmp/piusb/box_cpu_serial_number'
eth_mac_p_file='/tmp/piusb/box_eth_mac_number'
wlan_mac_p_file='/tmp/piusb/box_wlan_mac_number'

#check piusb mounted, if not mounted, mount it
mkdir -p /tmp/piusb
res=$(mountpoint "/tmp/piusb")
echo $res
if [[ $res == *"not"* ]]; then
	mount /home/root/piusb.bin /tmp/piusb
	echo mount piusb
fi

#read pi cpu searial
cpuinfo_file="/proc/cpuinfo"
while IFS= read -r line
do
	if [[ $line == *"Serial"* ]]; then
		echo "$line"
		cpu_serial_number_info=$line
	fi
done < "$cpuinfo_file"

echo "cpu_serial_number_info is"$cpu_serial_number_info

IFS=' '
read -r -a array <<< "$cpu_serial_number_info"
cpu_serial_number=${array[1]}
echo $cpu_serial_number >> "/tmp/piusb/box_cpu_serial_number"

#read eth mac
NET_ETH0_IFACE='eth0'
read ETH0_MAC </sys/class/net/$NET_ETH0_IFACE/address
echo $NET_ETH0_IFACE $ETH0_MAC
echo $ETH0_MAC >> $eth_mac_p_file


#read wifi mac
NET_WLAN0_IFACE='wlan0'
read WLAN0_MAC </sys/class/net/$NET_WLAN0_IFACE/address
echo $NET_WLAN0_IFACE $WLAN0_MAC
echo $WLAN0_MAC >> $wlan_mac_p_file

#sync box serial number
box_sn_file="/tmp/piusb/box_serial_number"
if [[ -f $box_sn_file ]];then
	while IFS= read -r line
	do
		echo $line
		if [[ $line == *"TLED"* ]]; then
			echo $line > /etc/hostname
		fi
	done < "$box_sn_file"
else
	echo "no box_sn_file"
fi




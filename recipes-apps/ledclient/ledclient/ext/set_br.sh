#!/bin/sh

COUNT_MAX=30
COUNT=0

while [ $COUNT -le $COUNT ]
do
    # The usb power on/off seq does not match microsnow eth hub,
    # only davicom udb dongle could work.
    # Sometimes the microsnow eth hub could not send the TX packet after power seq 
	if [ -e /sys/class/net/enp1s0u1u1 ];then
	    echo "power off usb hub"
	    uhubctl -l 1-1 -p 3 -a 0
	    echo "power on usb hub A"
	    sleep 2
	    uhubctl -l 1-1 -p 3 -a 1
	    sleep 4
            sync
	    echo "power seq end"
	elif [ -e /sys/class/net/enp1s0u1u1u4 ];then
	    echo "power off usb hub"
        # if only power off the hub 1-1 port 1, the power will be immediately on, 
        # so we power off the hub 1-1
	    uhubctl -l 1-1 -a 0
	    echo "power on usb hub A"
	    sleep 4
	    uhubctl -l 1-1 -a 1
	    sleep 4
            sync
	    echo "power seq end"
        fi
	(( COUNT ++ ))
	if [ -e /sys/class/net/enp1s0u1u1u4 ];then
		echo "find enp1s0u1u1u4"
		break
	elif [ -e /sys/class/net/enp1s0u1u1 ];then
		echo "find enp1s0u1u1"
		break
	else
		echo "no usb2eth"
		sleep 1
	fi
	echo "COUNT:$COUNT" >> /home/root/br_tmp.txt
done
echo "find usb2eth" >> /home/root/br_tmp.txt

if [ -e /sys/class/net/enp1s0u1u1u4 ];then
    	if [ -e /sys/class/net/br0 ];then
		pkill udhcpc	
        	ifconfig br0 down
        	ifconfig eth0 down
        	ifconfig enp1s0u1u1u4 down
        	brctl delbr br0
	fi
    ifconfig eth0 up
    ifconfig enp1s0u1u1u4 up
	echo "enp1s0u1u1u4 exists" >> /home/root/br_tmp.txt
	pkill dnsmasq #for sure that all client request ip from server
	brctl addbr br0
    nmcli con add con-name eth0 type ethernet ifname eth0 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    nmcli con add con-name enp1s0u1u1u4 type ethernet ifname enp1s0u1u1u4 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    nmcli con up eth0
    nmcli con up enp1s0u1u1u4
	brctl addif br0 eth0 
	brctl addif br0 enp1s0u1u1u4 
	ifconfig br0 up
	gen_mac_with_sn.py
	udhcpc -i br0 &
elif [ -e /sys/class/net/enp1s0u1u1 ];then
    if [ -e /sys/class/net/br0 ];then
        pkill udhcpc	
        ifconfig br0 down
        ifconfig eth0 down
        ifconfig enp1s0u1u1 down
        brctl delbr br0
	fi
    ifconfig eth0 up
    ifconfig enp1s0u1u1 up
	echo "enp1s0u1u1 exists" >> /home/root/br_tmp.txt
	pkill dnsmasq #for sure that all client request ip from server
	brctl addbr br0
    nmcli con add con-name eth0 type ethernet ifname eth0 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    nmcli con add con-name enp1s0u1u1 type ethernet ifname enp1s0u1u1 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    nmcli con up eth0
    nmcli con up enp1s0u1u1
	brctl addif br0 eth0 
	brctl addif br0 enp1s0u1u1
	ifconfig br0 up
	gen_mac_with_sn.py
	udhcpc -i br0 &
else
	echo "enp1s0u1u1u4 do not exists"
	udhcpc -i eth0 &
fi	

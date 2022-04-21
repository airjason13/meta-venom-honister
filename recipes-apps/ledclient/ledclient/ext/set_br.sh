#!/bin/sh

COUNT_MAX=30
COUNT=0

while [ $COUNT -le $COUNT ]
do
	(( COUNT ++ ))
	if [ -e /sys/class/net/enp1s0u1u1u4 ];then
		break
	else
		sleep 1
	fi
	echo "COUNT:$COUNT" >> /home/root/br_tmp.txt
done

if [ -e /sys/class/net/enp1s0u1u1u4 ];then
    	if [ -e /sys/class/net/br0 ];then
		pkill udhcpc	
        	ifconfig br0 down
        	brctl delbr br0
	fi
	echo "enp1s0u1u1u4 exists"
	pkill dnsmasq #for sure that all client request ip from server
	brctl addbr br0
    	nmcli con add con-name eth0 type ethernet ifname eth0 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    	nmcli con add con-name enp1s0u1u1u4 type ethernet ifname enp1s0u1u1u4 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    	nmcli con up eth0
    	nmcli con up enp1s0u1u1u4
	#brctl stp br0 off
	brctl addif br0 eth0 
	brctl addif br0 enp1s0u1u1u4 
	ifconfig eth0 0.0.0.0
	ifconfig enp1s0u1u1u4 0.0.0.0
	ifconfig br0 up
	udhcpc -i br0 &
	#route add -net 224.0.0.0 netmask 224.0.0.0 br0
else
	echo "enp1s0u1u1u4 do not exists"
	udhcpc -i eth0 &
fi	


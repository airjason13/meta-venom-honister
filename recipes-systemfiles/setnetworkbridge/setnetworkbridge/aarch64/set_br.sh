#!/bin/sh
if [ -e /sys/class/net/enp1s0u1u1u4 ];then
	echo "enp1s0u1u1u4 exists"
	pkill dnsmasq #for sure that all client request ip from server
	brctl addbr br0
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


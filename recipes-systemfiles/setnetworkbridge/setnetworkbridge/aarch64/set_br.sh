#!/bin/sh
if [ -e /sys/class/net/enp1s0u1u1u4 ];then
	echo "enp1s0u1u1u4 exists"
	brctl addbr br0
	brctl stp br0 off
	brctl addif br0 eth0 
	brctl addif br0 enp1s0u1u1u4 
	ifconfig br0 up
	udhcpc -i br0 &
else
	echo "enp1s0u1u1u4 do not exists"
	udhcpc -i eth0 &
fi	


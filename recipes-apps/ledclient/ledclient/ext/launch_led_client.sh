#!/bin/sh
while :
do
	br0_ip=$(/sbin/ifconfig br0 | grep 'inet addr:' | cut -d: -f2| cut -d' ' -f1)
	echo "br0 ip:"$br0_ip >> /home/root/.ledclient_network.log

	if [[ $br0_ip == 192.168.0.* ]];then
		echo "Abr0 ip:"$br0_ip >> /home/root/.ledclient_network.log
		ledclient -fflags nobuffer udp://239.11.11.11:15000
	else
		echo "no ip obtain!"
		sleep 3	
	fi
done	


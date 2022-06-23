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
	sudo echo "COUNT:$COUNT" >> /home/gisled/br_tmp.txt
done

if [ -e /sys/class/net/enp1s0u1u1u4 ];then
    	if [ -e /sys/class/net/br0 ];then
		    sudo pkill udhcpc	
        	sudo /sbin/ifconfig br0 down
        	sudo /sbin/ifconfig eth0 down
        	sudo /sbin/ifconfig enp1s0u1u1u4 down
        	sudo /usr/sbin/brctl delbr br0
	    fi
        sudo /sbin/ifconfig eth0 up
        sudo /sbin/ifconfig enp1s0u1u1u4 up
	    echo "enp1s0u1u1u4 exists"
	    sudo pkill dnsmasq #for sure that all client request ip from server
	    sudo /sbin/brctl addbr br0
    	sudo nmcli con add con-name eth0 type ethernet ifname eth0 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    	sudo nmcli con add con-name enp1s0u1u1u4 type ethernet ifname enp1s0u1u1u4 ip4 0.0.0.0/24 gw4 0.0.0.0 ipv4.method manual
    	#sudo nmcli con up eth0
    	#sudo nmcli con up enp1s0u1u1u4
	    sudo /usr/sbin/brctl stp br0 off
	    sudo /usr/sbin/brctl addif br0 eth0 
	    sudo /usr/sbin/brctl addif br0 enp1s0u1u1u4 
    	#nmcli con up eth0
	    sudo /sbin/ifconfig br0 up
        sudo nmcli con add con-name br0 ifname br0 autoconnect yes type ethernet
        sudo nmcli con up br0
else
	    echo "enp1s0u1u1u4 do not exists"
        sudo nmcli con add con-name eth0 ifname eth0 autoconnect yes type ethernet
        sudo nmcli con up eth0 
fi	


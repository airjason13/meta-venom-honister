#!/bin/sh

while :
do
	python3 /home/root/i2c_lcd_server/lcd_show.py 0:0:LCDCLIENT
	python3 /home/root/i2c_lcd_server/lcd_show.py 0:1:CONNECTING
	br0_ip=$(sudo /sbin/ifconfig br0 | grep 'inet addr:' | cut -d: -f2| cut -d' ' -f1)
	echo "br0 ip:"$br0_ip >> /home/root/.ledclient_network.log

	if [[ $br0_ip == 192.168.0.* ]];then
		echo "Abr0 ip:"$br0_ip >> /home/root/.ledclient_network.log
		ledclient -fflags nobuffer udp://239.11.11.11:15000
		sleep 1
        #if ledclient stop, let the br0 setup again to check eth hub 
		echo "set br again!"
		set_br.sh
	else
		echo "no ip obtain!"
		sleep 3	
	fi
done	


#!/bin/sh
CONFIG_FILE='/home/gisled/led_role.conf'
ROLE=''
RA_TAG='RA'
CLIENT_TAG='Client'
SERVER_TAG='Server'
AIO_TAG='AIO'
PLAYER_TAG='Player'
TESTER_TAG='Tester'
#for auto-mount test
udiskie &


if [ -e /home/gisled/server_now ];then
    sudo rm /home/gisled/server_now
fi

if [ -e /home/gisled/server_ra_now ];then
    sudo rm /home/gisled/server_ra_now
fi

if [ -e /home/gisled/client_now ];then
    sudo rm /home/gisled/client_now
fi

if [ -e /home/gisled/aio_now ];then
    sudo rm /home/gisled/aio_now
fi

if [ -e /home/gisled/client_ra_now ];then
    sudo rm /home/gisled/client_ra_now
fi
    
if [ -e /home/gisled/player_now ];then
    sudo rm /home/gisled/player_now
fi

if [ -e /home/gisled/tester_now ];then
    sudo rm /home/gisled/tester_now
fi

if [ -e $CONFIG_FILE ];then
    echo "config file exist"
    while read line; do
        echo $line
	line_size=${#line}
	echo "$line_size"
	if [[ $line_size == 0 ]];then
	    echo "no line"
        else	    
            if [[ $line =~ $SERVER_TAG ]];then
                if [[ $line =~ $RA_TAG ]];then
		            echo "Server_RA check"
		            ROLE=Server_RA
                else
		            ROLE=Server
		        fi
            elif [[ $line =~ $CLIENT_TAG ]];then
	            echo "Client check"
	            if [[ $line =~ $RA_TAG ]];then
	                echo "Client_RA check"
            	    ROLE=Client_RA
	            else
		            ROLE=Client
	            fi	
            elif [[ $line =~ $AIO_TAG ]];then
                echo "AIO check"
                ROLE=AIO
            elif [[ $line =~ $PLAYER_TAG ]];then
                ROLE=Player
            elif [[ $line =~ $TESTER ]];then
	            echo "Tester check"
                ROLE=Tester
            fi     
	fi    
    done < $CONFIG_FILE
    echo "ROLE:"$ROLE
else
    echo "gen a default config file as Client"
fi     

sudo insmod /home/gisled/rtl8812au_module/88XXau.ko

#modprobe v4l2loopback
sudo modprobe v4l2loopback video_nr=3,4,5,6

#for monitor temperature
sudo b_measure_temp.sh &

echo "ROLE:"$ROLE
if [[ $ROLE == *$CLIENT_TAG* ]];then
    echo "Let's set client env"
    if [[ $ROLE == *$RA_TAG* ]];then
        sudo ra_client.py &
    	sudo check_client_peripheral_devices.sh &
        sudo touch /home/gisled/client_ra_now
    else
        sudo touch /home/gisled/client_now	    
    fi
    echo "1. set_br"
    sudo set_br.sh 
    #turn the wifi off
    sudo nmcli radio wifi off 
    echo "2. check ip and launch ledclient"
    sudo launch_led_client.sh
elif [[ $ROLE == *$PLAYER_TAG* ]];then
    sudo touch /home/gisled/player_now
    echo "Just a simple player"
    sudo nmcli radio wifi on 
    sudo setup_hotspot.sh &
    sudo run-filemanager.sh &
    sudo launch_led_player.sh
elif [[ $ROLE == *$AIO_TAG* ]];then
    sudo touch /home/gisled/aio_now
    echo "AIO Now"
    sudo nmcli con add type ethernet ifname eth0 con-name eth0
    sudo nmcli con mod eth0 ipv4.addresses 192.168.0.3/24
    sudo nmcli con mod eth0 ipv4.gateway 192.168.0.3
    sudo nmcli con mod eth0 ipv4.dns "8.8.8.8"
    sudo nmcli con mod eth0 ipv4.method manual
    sudo nmcli con up eth0
    sudo nmcli radio wifi on 
    sudo setup_hotspot.sh &
    sudo setup_hotspot_alfa.sh &
    # setup_eth0_static.sh &
    # run-filemanager.sh &
    sudo launch_pyLedServer.sh &
    sudo write_tc358743_edid.sh & 
    sudo launch_led_aio_client.sh &
    
elif [[ $ROLE == *$SERVER_TAG* ]];then
    sudo echo "Server Now"
    #ifconfig eth0 192.168.0.3
    sudo nmcli con add type ethernet ifname eth0 con-name eth0
    sudo nmcli con mod eth0 ipv4.addresses 192.168.0.3/24
    sudo nmcli con mod eth0 ipv4.gateway 192.168.0.3
    sudo nmcli con mod eth0 ipv4.dns "8.8.8.8"
    sudo nmcli con mod eth0 ipv4.method manual
    sudo nmcli con up eth0
    sudo nmcli radio wifi on 
    sudo setup_hotspot.sh &
    sudo setup_hotspot_alfa.sh &
    sudo setup_eth0_static.sh &
    sudo run-filemanager.sh &
    sudo launch_pyLedServer.sh &
    sudo write_tc358743_edid.sh & 
    if [[ $ROLE == *$RA_TAG* ]];then
        sudo ra_client.py &
        sudo check_server_peripheral_devices.sh &
        sudo launch_pyLedRATool.sh &
        sudo touch /home/gisled/server_ra_now
    else
        sudo touch /home/gisled/server_now
    fi	    
elif [[ $ROLE == *$TESTER* ]];then
    sudo touch /home/gisled/tester_now
    sudo echo "Tester Now"
    sudo mcli radio wifi on 
    sudo setup_hotspot_tester.sh &
    sudo run-filemanager.sh &
    sudo launch_pyLedTester.sh 
fi  

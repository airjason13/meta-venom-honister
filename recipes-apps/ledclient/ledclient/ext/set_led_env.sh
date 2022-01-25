#!/bin/sh
CONFIG_FILE='/home/root/led_role.conf'
ROLE=''
RA_TAG='RA'
CLIENT_TAG='Client'
SERVER_TAG='Server'
PLAYER_TAG='Player'
TESTER_TAG='Tester'
#for auto-mount test
udiskie &


if [ -e /home/root/server_now ];then
    rm /home/root/server_now
fi

if [ -e /home/root/server_ra_now ];then
    rm /home/root/server_ra_now
fi

if [ -e /home/root/client_now ];then
    rm /home/root/client_now
fi

if [ -e /home/root/client_ra_now ];then
    rm /home/root/client_ra_now
fi
    
if [ -e /home/root/player_now ];then
    rm /home/root/player_now
fi

if [ -e /home/root/tester_now ];then
    rm /home/root/tester_now
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

insmod /home/root/rtl8812au_module/88XXau.ko

#for monitor temperature
b_measure_temp.sh &

echo "ROLE:"$ROLE
if [[ $ROLE == *$CLIENT_TAG* ]];then
    echo "Let's set client env"
    if [[ $ROLE == *$RA_TAG* ]];then
        ra_client.py &
    	check_client_peripheral_devices.sh &
        touch /home/root/client_ra_now
    else
        touch /home/root/client_now	    
    fi
    echo "1. set_br"
    set_br.sh 
    #turn the wifi off
    nmcli radio wifi off 
    echo "2. check ip and launch ledclient"
    launch_led_client.sh
elif [[ $ROLE == *$PLAYER_TAG* ]];then
    touch /home/root/player_now
    echo "Just a simple player"
    nmcli radio wifi on 
    setup_hotspot.sh &
    run-filemanager.sh &
    launch_led_player.sh
elif [[ $ROLE == *$SERVER_TAG* ]];then
    echo "Server Now"
    ifconfig eth0 192.168.0.3
    nmcli radio wifi on 
    setup_hotspot.sh &
    run-filemanager.sh &
    launch_pyLedServer.sh & 
    if [[ $ROLE == *$RA_TAG* ]];then
        ra_client.py &
        check_server_peripheral_devices.sh &
        launch_pyLedRATool.sh &
        touch /home/root/server_ra_now
    else
        touch /home/root/server_now
    fi	    
elif [[ $ROLE == *$TESTER* ]];then
    touch /home/root/tester_now
    echo "Tester Now"
    nmcli radio wifi on 
    setup_hotspot_tester.sh &
    run-filemanager.sh &
    launch_pyLedTester.sh 
fi  

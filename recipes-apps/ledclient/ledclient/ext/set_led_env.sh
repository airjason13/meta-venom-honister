#!/bin/sh
CONFIG_FILE='/home/root/led_role.conf'
ROLE=''
CLIENT_TAG='Client'
SERVER_TAG='Server'
PLAYER_TAG='Player'
TESTER_TAG='Tester'

#for auto-mount test
udiskie &


if [ -e /home/root/server_now ];then
    rm /home/root/server_now
fi

if [ -e /home/root/client_now ];then
    rm /home/root/client_now
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
        if [[ $SERVER_TAG == $line ]];then
            ROLE=Server
        elif [[ $CLIENT_TAG == $line ]];then
            ROLE=Client
        elif [[ $PLAYER_TAG == $line ]];then
            ROLE=Player
        elif [[ $TESTER_TAG == $line ]];then
            ROLE=Tester
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
if [[ $CLIENT_TAG == $ROLE ]];then
    touch /home/root/client_now
    echo "Let's set client env"
    check_client_peripheral_devices.sh &
    echo "1. set_br"
    set_br.sh
	#turn the wifi off
	nmcli radio wifi off 
	echo "2. check ip and launch ledclient"
	launch_led_client.sh
elif [[ $PLAYER_TAG == $ROLE ]];then
    touch /home/root/player_now
    echo "Just a simple player"
	nmcli radio wifi on 
    setup_hotspot.sh &
	run-filemanager.sh &
    launch_led_player.sh
elif [[ $SERVER_TAG == $ROLE ]];then
    touch /home/root/server_now
    check_server_peripheral_devices.sh &
    echo "Server Now"
	nmcli radio wifi on 
    setup_hotspot.sh &
	run-filemanager.sh &
	launch_pyLedServer.sh 
elif [[ $TESTER_TAG == $ROLE ]];then
    touch /home/root/tester_now
    echo "Tester Now"
	nmcli radio wifi on 
    setup_hotspot_tester.sh &
	run-filemanager.sh &
	launch_pyLedTester.sh 
fi  

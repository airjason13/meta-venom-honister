#!/bin/sh
CONFIG_FILE='/home/root/led_role.conf'
ROLE=''
CLIENT_TAG='Client'
SERVER_TAG='Server'
PLAYER_TAG='Player'

if [ -e /home/root/server_now ];then
    rm /home/root/server_now
fi

if [ -e /home/root/client_now ];then
    rm /home/root/client_now
fi
    
if [ -e /home/root/player_now ];then
    rm /home/root/player_now
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
        fi     
    done < $CONFIG_FILE
    echo "ROLE:"$ROLE
else
    echo "gen a default config file as Client"
fi     

echo "ROLE:"$ROLE
if [[ $CLIENT_TAG == $ROLE ]];then
    touch /home/root/client_now
    echo "Let's set client env"
    echo "1. set_br"
    set_br.sh
	echo "2. check ip and launch ledclient"
	launch_led_client.sh
elif [[ $PLAYER_TAG == $ROLE ]];then
    touch /home/root/player_now
    echo "Just a simple player"
    launch_led_player.sh
elif [[ $SERVER_TAG == $ROLE ]];then
    touch /home/root/server_now
    echo "Server Now"
    launch_pyLedServer.sh 
fi  

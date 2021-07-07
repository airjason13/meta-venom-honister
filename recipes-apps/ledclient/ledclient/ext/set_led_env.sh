#!/bin/sh
CONFIG_FILE='/home/root/led_role.conf'
ROLE=''
CLIENT_TAG='Client'
SERVER_TAG='Server'
if [ -e /home/root/server_now ];then
    rm /home/root/server_now
fi

if [ -e /home/root/client_now ];then
    rm /home/root/client_now
fi
    
if [ -e $CONFIG_FILE ];then
    echo "config file exist"
    while read line; do
        echo $line
        if [[ $SERVER_TAG == $line ]];then
            ROLE=Server
        elif [[ $CLIENT_TAG == $line ]];then
            ROLE=Client
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
else
    touch /home/root/server_now
    echo "Server Now"
    launch_pyLedServer.sh 
fi  

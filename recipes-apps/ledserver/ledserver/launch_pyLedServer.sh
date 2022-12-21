#!/bin/sh
#make bt discoverable
bt_discoverable.sh

#add bt SP service
sdptool add SP

#setup bt sp server
python2 /usr/bin/rfcomm-server-sdp.py &


cd /home/root/pyLedServer
while :
do
    pkill -f pyzmq_server_rep.py
    python3 /home/root/pyzmq_server_rep/pyzmq_server_rep.py &

	python3 main.py
	sleep 2
done	

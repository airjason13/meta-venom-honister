#!/bin/sh
#make bt discoverable
bt_discoverable.sh

#add bt SP service
sdptool add SP

#setup bt sp server
python2 /usr/bin/rfcomm-server-sdp.py &


cd /home/root/pyLedServer
python3 main.py

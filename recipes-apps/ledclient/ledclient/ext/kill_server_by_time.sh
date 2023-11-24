#!/bin/sh

while :
do
	sleep 14000
	pkill -f main.py
	echo "kill server@"$(date) > /home/root/kill_server_time.txt
done

#!/bin/sh

#sleep for wait vcgencmd ok
sleep 30

FILE_URI='/home/root/check_server_peripheral_devices.dat'
#echo Start to check > 

while :
do
    #check ethernet
    ETH_LOG=$(ethtool eth0 | grep Link)
    if [[ $ETH_LOG == *"yes"* ]]; then
	echo "eth0 get link"
    else
	echo "eth0 link missing"
        TEMP=$(vcgencmd measure_temp | cut -c 6-7)
	CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-)
        echo TEMP=$TEMP at $CPU_CLOCK hz
        echo ETH Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_server_peripheral_devices.dat
    fi
    #check lcd1602
    ETH_LOG=$(i2cdetect -y 1 | grep 27)
    if [[ $ETH_LOG == *"27"* ]]; then
	    echo "lcd1602 alive"
    else
	    echo "lcd1602 missing"
        TEMP=$(vcgencmd measure_temp | cut -c 6-7)
	    CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-)
        echo TEMP=$TEMP at $CPU_CLOCK hz
        echo lcd1602 Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_server_peripheral_devices.dat
    fi
    sleep 60
done

#!/bin/sh

#sleep for wait vcgencmd ok
sleep 30

FILE_URI='/home/root/check_client_peripheral_devices.dat'
#echo Start to check > 

while :
do
    #check usb pico
    USB_LOG=$(lsusb -d 0x0000:0x0001)
    echo USB_LOG=$USB_LOG
    if [[ $USB_LOG == *"Pico"* ]]; then
	echo "pico alive"
    else
    	echo "pico missing"
        TEMP=$(vcgencmd measure_temp | cut -c 6-7)
	    CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-)
        echo TEMP=$TEMP at $CPU_CLOCK hz
        echo Pico Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_client_peripheral_devices.dat
    fi	

    #check usb terminus
    USB_LOG=$(lsusb -d 0x1a40:0x0101)
    if [[ $USB_LOG == *"Terminus"* ]]; then
	echo "eth/usb hub alive"
    else
    	echo "eth/usb hub missing"
        TEMP=$(vcgencmd measure_temp | cut -c 6-7)
	    CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-)
        echo TEMP=$TEMP at $CPU_CLOCK hz
        echo Terminus Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_client_peripheral_devices.dat
    fi	

    #check ethernet
    ETH_LOG=$(ethtool br0 | grep Link)
    if [[ $ETH_LOG == *"yes"* ]]; then
	echo "br0 get link"
    else
	echo "br0 link missing"
        TEMP=$(vcgencmd measure_temp | cut -c 6-7)
	    CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-)
        echo TEMP=$TEMP at $CPU_CLOCK hz
        echo ETH Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_client_peripheral_devices.dat
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
        echo lcd1602 Missing, TEMP=$TEMP at $CPU_CLOCK hz >> /home/root/check_client_peripheral_devices.dat
    fi
    sleep 60
done

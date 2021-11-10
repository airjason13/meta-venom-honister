#!/bin/sh
HIGHEST_TEMP=0
CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-18)

while :
do 
    TEMP=$(vcgencmd measure_temp | cut -c 6-7)
    if [ $TEMP -gt $HIGHEST_TEMP ];then
        HIGHEST_TEMP=$TEMP
        echo HIGHEST_TEMP=$HIGHEST_TEMP at $CPU_CLOCK Mhz
        echo HIGHEST_TEMP=$HIGHEST_TEMP at $CPU_CLOCK Mhz > ~/temperature.dat
    fi
    sleep 3
done

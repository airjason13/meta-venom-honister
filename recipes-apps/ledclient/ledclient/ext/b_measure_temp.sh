#!/bin/sh
FILE_URI='/home/root/temperature.dat'
if [ -f $FILE_URI ];then
	HIGHEST_TEMP=0
	while read line
	do 

    		HIGHEST_TEMP=$(echo $line | cut -c 14-15)
   		echo "ori highest temp = "$HIGHEST_TEMP
	done < $FILE_URI
else
	HIGHEST_TEMP=0
fi

CPU_CLOCK=$(vcgencmd measure_clock arm | cut -c 15-18)

while :
do 
    TEMP=$(vcgencmd measure_temp | cut -c 6-7)
    if [ $TEMP -gt $HIGHEST_TEMP ];then
        HIGHEST_TEMP=$TEMP
        echo HIGHEST_TEMP=$HIGHEST_TEMP at $CPU_CLOCK Mhz
        echo HIGHEST_TEMP=$HIGHEST_TEMP at $CPU_CLOCK Mhz > /home/root/temperature.dat
    fi
    sleep 3
done

#!bin/sh


res=$(lsusb|wc -l)

if [ "$res" -le "1" ]; then
	echo "0";
 else
 	echo "1";
 fi

 
#!bin/sh

addr=192.168.0.1
ping $addr -c 1 -W 1 >/dev/zero
#res=$(echo $?)

if [ "$?" -eq "1" ]; then
	echo "0";
 else
 	echo "1";
 fi
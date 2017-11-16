#!bin/sh


res=$(lspci|grep 6869)

if [ -z "$res" ]; then
	echo "0";
 else
 	echo "1";
 fi

 
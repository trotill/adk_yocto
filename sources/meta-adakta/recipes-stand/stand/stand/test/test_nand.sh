#!bin/sh

if [ -e "/dev/mtdblock0" ]; then
  dd if=/dev/mtdblock0 of=/var/run/nand bs=1 count=10

  echo "ADAKTATEST">/dev/mtdblock0
  dd if=/dev/mtdblock0 of=/var/run/nand.adaktatest bs=1 count=10
  DATA=$(cat /var/run/nand.adaktatest)
  if [ $DATA == "ADAKTATEST" ]; then
        echo "1"
  else
        echo "0"
  fi
else
 echo "0"
fi

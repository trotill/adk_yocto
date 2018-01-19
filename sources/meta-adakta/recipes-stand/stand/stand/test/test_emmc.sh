#!bin/sh

(
echo o
echo n
echo p
echo 1
echo
echo
echo w
) | fdisk /dev/mmcblk$1>/dev/zero 2>&1

sleep 1
if [ -e "/dev/mmcblk$1p1" ]; then
 echo "1"
else
 echo "0"
fi

 
#!bin/sh

export DISPLAY=":0.0"


echo -e $1 | xmessage -file -&

#xmessage $1&
#echo Show message $1

#exit 1
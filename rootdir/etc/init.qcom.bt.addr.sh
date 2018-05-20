#!system/bin/sh
bdaddr=`cat /persist/bd_addr.txt`
setprop ro.boot.btmacaddr $bdaddr

#!system/bin/sh

FSG_HEAD=`getprop ro.fsg_head`
FSG_DEVICE=/dev/block/bootdevice/by-name/fsg
FS_IMAGE_PATH=/system/etc/
#VERSION_ID=`cat /sys/hwinfo/version_id`
#QCN_TYPE=`cat /sys/hwinfo/qcn_type`
CURRENT_FSG_IMG="non_ca_fs_image.tar.gz.mbn.img"

if [ $FSG_HEAD == "1" ];then
	exit 0
fi


function copy_to_fsg() {
    echo $FS_IMAGE_PATH
    echo $FSG_DEVICE

    dd if=$FS_IMAGE_PATH/$CURRENT_FSG_IMG of=$FSG_DEVICE
}

function select_fsg_image() {
#fs image 
#   ca_fs_image.tar.gz.mbn.img
#   fs_image.tar.gz.mbn.img
#   non_ca_fs_image.tar.gz.mbn.img

#version_id
#   primary      ---non_ca_fs_image.tar.gz.mbn.img
#   standard     ---non_ca_fs_image.tar.gz.mbn.img
#   advanced     ---ca_fs_image.tar.gz.mbn.img
    CURRENT_FSG_IMG="fs_image.tar.gz.mbn.img"
    echo $CURRENT_FSG_IMG

}


if [ $FSG_HEAD == "0" ];then
    select_fsg_image
    copy_to_fsg 
fi

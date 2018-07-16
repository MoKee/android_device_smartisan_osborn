#!/sbin/sh
#
# Copyright (C) 2018 The MoKee Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

SGDISK=/tmp/install/bin/sgdisk

BLOCKDEV=/dev/block/bootdevice/mmcblk0

SYSTEM=/dev/block/bootdevice/by-name/system
VENDOR=/dev/block/bootdevice/by-name/vendor

OUTFD=0

for FD in `ls /proc/$$/fd`; do
  readlink /proc/$$/fd/$FD 2>/dev/null | grep pipe >/dev/null
  if [ "$?" -eq "0" ]; then
    ps | grep " 3 $FD " | grep -v grep >/dev/null
    if [ "$?" -eq "0" ]; then
      OUTFD=$FD
      break
    fi
  fi
done

ui_print() {
  echo -e "ui_print $1\nui_print" >> /proc/self/fd/$OUTFD
}

safe_exec() {
   cmd="$@"
   $cmd
   ret=$?
   if [ ${ret} != 0 ]; then
      ui_print "! Error when executing command: '${cmd}'\n"
      exit ${ret}
   fi
}

if [ ! -e "$VENDOR" ]; then
    ui_print "- No /vendor, do repartition..."

    ui_print "- Removing /system"
    safe_exec "$SGDISK --delete 43 $BLOCKDEV"

    ui_print "- Creating /system"
    safe_exec "$SGDISK --new 0:0:+3G --change-name 43:system $BLOCKDEV"

    ui_print "- Creating /vendor"
    safe_exec "$SGDISK --new 0:0 --change-name 50:vendor $BLOCKDEV"

    ui_print "- Formating /system"
    safe_exec "make_ext4fs $SYSTEM"

    ui_print "- Formating /vendor"
    safe_exec "make_ext4fs $VENDOR"

    ui_print "- Done!"
else
    ui_print "- Good! Found /vendor"
fi

exit 0

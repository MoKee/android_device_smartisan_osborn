#!/bin/bash
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

set -e

DEVICE=osborn
VENDOR=smartisan

# Load extract_utils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$MY_DIR" ]]; then MY_DIR="$PWD"; fi

MK_ROOT="$MY_DIR"/../../..

HELPER="$MK_ROOT"/vendor/mk/build/tools/extract_utils.sh
if [ ! -f "$HELPER" ]; then
    echo "Unable to find helper script at $HELPER"
    exit 1
fi
. "$HELPER"

# Default to sanitizing the vendor folder before extraction
CLEAN_VENDOR=true

SRC=$1
SRC_QC=$2

if [ -z "$SRC" ]; then
    SRC=adb
fi

# Initialize the helper
setup_vendor "$DEVICE" "$VENDOR" "$MK_ROOT" false "$CLEAN_VENDOR"

extract "$MY_DIR"/proprietary-files.txt "$SRC" "$SECTION"
extract "$MY_DIR"/proprietary-files-qc.txt "$SRC_QC" "$SECTION"
extract "$MY_DIR"/proprietary-files-qc-perf.txt "$SRC_QC" "$SECTION"

BLOB_ROOT="$MK_ROOT"/vendor/"$VENDOR"/"$DEVICE"/proprietary

# Audio
sed -i 's|/system/etc/|/vendor/etc/|g' $BLOB_ROOT/vendor/lib/libacdbloader.so
sed -i 's|/system/etc/|/vendor/etc/|g' $BLOB_ROOT/vendor/lib64/libacdbloader.so

# Camera
sed -i 's|/system/etc/|/vendor/etc/|g' $BLOB_ROOT/vendor/lib/hw/camera.sdm660.so
sed -i 's|/system/etc/|/vendor/etc/|g' $BLOB_ROOT/vendor/lib/libmmcamera2_sensor_modules.so
sed -i 's|/system/etc/|/vendor/etc/|g' $BLOB_ROOT/vendor/lib/libmms_hal_vstab.so

# Fingerprint
sed -i 's|\x00fpcfingerprint\x00|\x00fingerprint\x00\x00\x00\x00|' $BLOB_ROOT/vendor/lib64/hw/fingerprint.fpc.so
sed -i 's|\x00goodixfingerprint\x00|\x00fingerprint\x00\x00\x00\x00\x00\x00\x00|' $BLOB_ROOT/vendor/lib64/hw/fingerprint.goodix.so

"$MY_DIR"/setup-makefiles.sh

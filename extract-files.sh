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
SRC_RIL=$3

if [ -z "$SRC" ]; then
    SRC=adb
fi

# Initialize the helper
setup_vendor "$DEVICE" "$VENDOR" "$MK_ROOT" false "$CLEAN_VENDOR"

extract "$MY_DIR"/proprietary-files.txt "$SRC" "$SECTION"
extract "$MY_DIR"/proprietary-files-qc.txt "$SRC_QC" "$SECTION"
extract "$MY_DIR"/proprietary-files-qc-perf.txt "$SRC_QC" "$SECTION"
extract "$MY_DIR"/proprietary-files-qc-ril.txt "$SRC_RIL" "$SECTION"

function fix_fpc () {
    sed -i \
        's/\x00fpcfingerprint\x00/\x00fingerprint\x00\x00\x00\x00/' \
        "$MK_ROOT"/vendor/"$VENDOR"/"$DEVICE"/proprietary/vendor/"$1"
}

fix_fpc lib64/hw/fingerprint.fpc.so

function fix_goodix () {
    sed -i \
        's/\x00goodixfingerprint\x00/\x00fingerprint\x00\x00\x00\x00\x00\x00\x00/' \
        "$MK_ROOT"/vendor/"$VENDOR"/"$DEVICE"/proprietary/vendor/"$1"
}

fix_goodix lib64/hw/fingerprint.goodix.so

function fix_vendor () {
    sed -i \
        "s/\/system\/$1\//\/vendor\/$1\//g" \
        "$MK_ROOT"/vendor/"$VENDOR"/"$DEVICE"/proprietary/vendor/"$2"
}

# Audio
fix_vendor etc lib/hw/audio.primary.sdm660.so
fix_vendor etc lib/libacdbloader.so
fix_vendor etc lib64/hw/audio.primary.sdm660.so
fix_vendor etc lib64/libacdbloader.so
fix_vendor lib lib/hw/audio.primary.sdm660.so
fix_vendor lib lib64/hw/audio.primary.sdm660.so

# Camera
fix_vendor etc lib/hw/camera.sdm660.so
fix_vendor etc lib/libmmcamera2_sensor_modules.so
fix_vendor etc lib/libmms_hal_vstab.so

"$MY_DIR"/setup-makefiles.sh

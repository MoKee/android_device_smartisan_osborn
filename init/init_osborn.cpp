/*
Copyright (c) 2013, The Linux Foundation. All rights reserved.
Copyright (c) 2018, The MoKee Open Source Project

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <android-base/file.h>
#include <android-base/strings.h>
#include <android-base/logging.h>

#include "vendor_init.h"
#include "property_service.h"

#define BOOT_REASON_FILE "/proc/sys/kernel/boot_reason"

using android::base::Trim;
using android::base::ReadFileToString;
using android::init::property_set;

void init_alarm_boot_properties()
{
    std::string boot_reason;

    if (ReadFileToString(BOOT_REASON_FILE, &boot_reason)) {
        /*
         * Setup ro.alarm_boot value to true when it is RTC triggered boot up
         * For existing PMIC chips, the following mapping applies
         * for the value of boot_reason:
         *
         * 0 -> unknown
         * 1 -> hard reset
         * 2 -> sudden momentary power loss (SMPL)
         * 3 -> real time clock (RTC)
         * 4 -> DC charger inserted
         * 5 -> USB charger inserted
         * 6 -> PON1 pin toggled (for secondary PMICs)
         * 7 -> CBLPWR_N pin toggled (for external power supply)
         * 8 -> KPDPWR_N pin toggled (power key pressed)
         */
        if (Trim(boot_reason) == "0") {
            property_set("ro.boot.bootreason", "invalid");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "1") {
            property_set("ro.boot.bootreason", "hard_reset");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "2") {
            property_set("ro.boot.bootreason", "smpl");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "3") {
            property_set("ro.alarm_boot", "true");
            // disable boot animation for RTC wakeup
            property_set("debug.sf.nobootanimation", "1");
        }
        else if (Trim(boot_reason) == "4") {
            property_set("ro.boot.bootreason", "dc_chg");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "5") {
            property_set("ro.boot.bootreason", "usb_chg");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "6") {
            property_set("ro.boot.bootreason", "pon1");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "7") {
            property_set("ro.boot.bootreason", "cblpwr");
            property_set("ro.alarm_boot", "false");
        }
        else if (Trim(boot_reason) == "8") {
            property_set("ro.boot.bootreason", "kpdpwr");
            property_set("ro.alarm_boot", "false");
        }
    }
    else {
        LOG(ERROR) << "Unable to read bootreason from " << BOOT_REASON_FILE;
    }
}

void vendor_load_properties() {
    LOG(INFO) << "Loading vendor specific properties";
    init_alarm_boot_properties();
}

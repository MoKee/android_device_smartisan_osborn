/*
 * Copyright 2016, The Android Open Source Project
 * Copyright 2018, The LineageOS Project
 * Copyright 2018, The MoKee Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG  "BtMacGenerator"

#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <cutils/log.h>
#include <cutils/properties.h>
#include <sys/stat.h>

#include <android-base/logging.h>

static int force_random = 0;
static const char PERSIST_BDADDR_PATH[] = "/persist/bd_addr.txt";
static const char VENDOR_BT_MAC_PATH[]  = "/data/vendor/mac_addr/bt.mac";

static void update_bt_mac(uint8_t *addr, bool random) {
    FILE *fd = NULL;
    struct stat st;

    if (random) {
        /* If file is exist and check its size or force reproduce it when first start bt */
        if (force_random == 0)
            force_random++;

        /* If file is exist and check its size */
        if (force_random != 1 && stat(VENDOR_BT_MAC_PATH, &st) == 0 && st.st_size >= 6) {
            ALOGD("%s: File %s already exists", __func__, VENDOR_BT_MAC_PATH);
            return;
        }

        srand(time(NULL));
        addr[0] = 0xb4;
        addr[1] = 0x0b;
        addr[2] = 0x44;
        addr[3] = (rand() & 0x0FF00000) >> 20;
        addr[4] = (rand() & 0x0FF00000) >> 20;
        addr[5] = (rand() & 0x0FF00000) >> 20;

        if (force_random == 1)
            force_random ++;
    }

    ALOGV("%s: BT Addr: %02x:%02x:%02x:%02x:%02x:%02x", __func__,
        addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    if ((fd = fopen(VENDOR_BT_MAC_PATH, "wb")) == NULL) {
        ALOGE("%s: Could not open bt mac file %s", __func__, VENDOR_BT_MAC_PATH);
        return;
    }

    ALOGD("%s: Writing BT addr to file %s", __func__, VENDOR_BT_MAC_PATH);
    fwrite(addr, sizeof(uint8_t), 6, fd);
    fclose(fd);

    chmod(VENDOR_BT_MAC_PATH, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
}

static void get_mac_from_persist() {
    struct stat st;
    FILE *fd;
    uint8_t *buf = (uint8_t *) malloc(6);
    int len = 0;
    bool random = false;

    if (stat(PERSIST_BDADDR_PATH, &st) != 0 || st.st_size < 17) {
        ALOGE("%s: Invalid BT addr file %s, will generate random mac", __func__, PERSIST_BDADDR_PATH);
        random = true;
    } else {
        // read nv files in binary mode
        if ((fd = fopen(PERSIST_BDADDR_PATH, "rb")) == NULL) {
            ALOGE("%s: Could not open BT addr file %s", __func__, PERSIST_BDADDR_PATH);
            random = true;
        }
    }
    if (!random) {
        if (fscanf(fd, "%02X:%02X:%02X:%02X:%02X:%02X", buf, buf + 1, buf + 2, buf + 3, buf + 4, buf + 5) != 6) {
            ALOGE("%s: Could not parse BT addr file %s", __func__, PERSIST_BDADDR_PATH);
            random = true;
        }
        fclose(fd);
    }
    update_bt_mac(buf, random);
    free(buf);
}

int main() {
    get_mac_from_persist();
    return 0;
}

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

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit from osborn device
$(call inherit-product, device/smartisan/osborn/device.mk)

# Inherit some common MK stuff.
$(call inherit-product, vendor/mk/config/common_full_phone.mk)

PRODUCT_PROPERTY_OVERRIDES += \
    ro.mk.maintainer=XiNGRZ

PRODUCT_NAME := mk_osborn
PRODUCT_BRAND := Smartisan
PRODUCT_DEVICE := osborn
PRODUCT_MANUFACTURER := smartisan
PRODUCT_MODEL := OS105

PRODUCT_GMS_CLIENTID_BASE := android-smartisan

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_NAME="osborn" \
    PRIVATE_BUILD_DESC="osborn-user 7.1.1 NGI77B 1 dev-keys"

BUILD_FINGERPRINT := Android/osborn/osborn:7.1.1/NGI77B/1536068833:user/dev-keys

# Sign bootable images
PRODUCT_SUPPORTS_BOOT_SIGNER := true
PRODUCT_SUPPORTS_VERITY := true
PRODUCT_VERITY_SIGNING_KEY := build/target/product/security/testkey

TARGET_VENDOR := Smartisan

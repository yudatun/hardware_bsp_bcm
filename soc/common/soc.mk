#
# Copyright 2016 The Android Open Source Project
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

LOCAL_PATH := hardware/bsp/bcm/soc/common

TARGET_BOOT_OUT := out/target/product/$(TARGET_DEVICE)/boot

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/init.bcm.rc:root/init.bcm.rc \
    $(LOCAL_PATH)/ueventd.bcm.rc:root/ueventd.bcm.rc \
    system/core/rootdir/init.usb.rc:root/init.usb.rc \
    system/core/rootdir/init.usb.configfs.rc:root/init.usb.configfs.rc \
    system/core/rootdir/ueventd.rc:root/ueventd.rc

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/initnetwork.sh:system/bin/initnetwork.sh

BOARD_SEPOLICY_DIRS += \
    $(LOCAL_PATH)/sepolicy

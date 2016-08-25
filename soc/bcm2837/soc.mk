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

LOCAL_PATH := hardware/bsp/bcm/soc/bcm2837

TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a
TARGET_CPU_VARIANT := generic
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_KERNEL_ARCH := $(TARGET_ARCH)

TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := false
TARGET_NO_RECOVERY := true

TARGET_USE_DISKINSTALLER := true
TARGET_PARTITION_TABLE_TYPE := MBR
TARGET_USERIMAGES_USE_EXT4 := true

# Set up the local kernel.
TARGET_KERNEL_SRC := hardware/bsp/kernel/bcm/linux
TARGET_KERNEL_DEFCONFIG := bcm2709_defconfig
$(call add_kernel_configs, $(realpath $(LOCAL_PATH)/soc.kconf))
TARGET_KERNEL_DTB := bcm2710-rpi-3-b.dtb

TARGET_BOOT_OUT := out/target/product/$(TARGET_DEVICE)/boot

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/init.bcm.rc:root/init.bcm.rc \
    system/core/rootdir/init.usb.configfs.rc:root/init.usb.configfs.rc \
    system/core/rootdir/ueventd.rc:root/ueventd.rc

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/initnetwork.sh:system/bin/initnetwork.sh

# TODO: Move common/prebuilts/sepolicy include to audio_prebuilts.mk
BOARD_SEPOLICY_DIRS += \
	$(LOCAL_PATH)/sepolicy

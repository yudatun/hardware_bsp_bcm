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

TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a
TARGET_CPU_VARIANT := generic
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_KERNEL_ARCH := $(TARGET_ARCH)

TARGET_USE_DISKINSTALLER := true
TARGET_PARTITION_TABLE_TYPE := MBR
TARGET_USERIMAGES_USE_EXT4 := true

# Set up the local kernel.
TARGET_KERNEL_SRC := hardware/bsp/kernel/bcm/linux
TARGET_KERNEL_DEFCONFIG := bcmrpi_defconfig

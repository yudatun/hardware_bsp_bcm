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

BLUETOOTH_BSP_SRC = hardware/bsp/bcm/peripheral/bluetooth/bcm43438

BLUETOOTH_DRIVER_HAL_PERIPHERAL := bcm43438

BOARD_SEPOLICY_DIRS += $(BLUETOOTH_BSP_SRC)/sepolicy

# Enable bluetooth
BOARD_HAVE_BLUETOOTH_BCM := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(BLUETOOTH_BSP_SRC)
BOARD_CUSTOM_BT_CONFIG := $(BLUETOOTH_BSP_SRC)/vnd_raspberrypi3.txt

########################################
DEVICE_PACKAGES += \
    bt_bcm \
    bt_vendor.conf \
    BCM43430A1.hcd \

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

ifeq ($(BLUETOOTH_DRIVER_HAL_PERIPHERAL),bcm43438)

LOCAL_PATH := $(call my-dir)

########################################
include $(CLEAR_VARS)

LOCAL_MODULE := bt_vendor.conf
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc/bluetooth
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := $(LOCAL_MODULE)

include $(BUILD_PREBUILT)

########################################
include $(CLEAR_VARS)

LOCAL_MODULE := BCM43430A1.hcd
LOCAL_MODULE_CLASS := DATA
LOCAL_MODULE_PATH := $(TARGET_OUT)/vendor/firmware
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := $(LOCAL_MODULE)

include $(BUILD_PREBUILT)

########################################
include $(CLEAR_VARS)

LOCAL_MODULE := bt_bcm
LOCAL_MODULE_TAGS := optional
LOCAL_REQUIRED_MODULES :=  \
    libbt-vendor \
    bluetooth.default \
    bluetooth-cli \
    bluetoothtbd \
    net_bdtool
LOCAL_INIT_RC := bt_bcm43438.rc

include $(BUILD_PHONY_PACKAGE)

endif

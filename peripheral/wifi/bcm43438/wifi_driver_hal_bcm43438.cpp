/*
 * Copyright (C) 2016 The Android Open Source Project
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <cutils/log.h>
#include <hardware_brillo/wifi_driver_hal.h>

const char kStationDeviceName[] = "wlan0";

/* Our HAL needs to set the AP/Station mode prior to actually initializing
 * the wifi. We use a dummy function for the initialize.
 */
static wifi_driver_error wifi_driver_initialize_bcm43438(void) {
    return WIFI_SUCCESS;
}

static wifi_driver_error wifi_driver_set_mode_bcm43438(
        wifi_driver_mode mode,
        char* wifi_device_name,
        size_t wifi_device_name_size)
{
    strlcpy(wifi_device_name, kStationDeviceName, sizeof(kStationDeviceName));
    return  WIFI_SUCCESS;
}

static int close_bcm43438_driver(struct hw_device_t *device) {
    wifi_driver_device_t *dev = reinterpret_cast<wifi_driver_device_t *>(device);
    if (dev)
        free(dev);
    return 0;
}

static int open_bcm43438_driver(
    const struct hw_module_t* module, const char*,
    struct hw_device_t** device)
{
    wifi_driver_device_t* dev = reinterpret_cast<wifi_driver_device_t *>(
        calloc(1, sizeof(wifi_driver_device_t)));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = WIFI_DRIVER_DEVICE_API_VERSION_0_1;

    // We're forced into this cast by the existing API.  This pattern is
    // common among users of the HAL.
    dev->common.module = (hw_module_t *)module;

    dev->common.close = close_bcm43438_driver;
    dev->wifi_driver_initialize = wifi_driver_initialize_bcm43438;
    dev->wifi_driver_set_mode = wifi_driver_set_mode_bcm43438;

    *device = &dev->common;

    return 0;
}

static struct hw_module_methods_t bcm43438_driver_module_methods = {
    .open = open_bcm43438_driver
};

hw_module_t HAL_MODULE_INFO_SYM = {
    .tag            = HARDWARE_MODULE_TAG,
    .version_major  = 1,
    .version_minor  = 0,
    .id             = WIFI_DRIVER_HARDWARE_MODULE_ID,
    .name           = "bcm43438 / RPi 3B module",
    .author         = "Yudatun",
    .methods        = &bcm43438_driver_module_methods,
    .dso            = NULL,
    .reserved       = {0},
};

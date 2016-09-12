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

#include <fcntl.h>
#include <unistd.h>

#include <cutils/log.h>
#include <hardware_brillo/wifi_driver_hal.h>

static wifi_driver_error wifi_driver_initialize_rtl8xxxu(void)
{
    return WIFI_SUCCESS;
}

static wifi_driver_error wifi_driver_set_mode_rtl8xxxu(
    wifi_driver_mode mode,
    char* wifi_device_name,
    size_t wifi_device_name_size)
{
    return WIFI_SUCCESS;
}

static int close_rtl8xxxu_driver(struct hw_device_t* device)
{
    wifi_driver_device_t* dev = reinterpret_cast<wifi_driver_device_t*>(device);
    if (dev)
        free(dev);
    return 0;
}

static int open_rtl8xxxu_driver(const struct hw_module_t* module, const char*,
                       struct hw_device_t** device)
{
    wifi_driver_device_t* dev = reinterpret_cast<wifi_driver_device_t*>(
        calloc(1, sizeof(wifi_driver_device_t)));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = WIFI_DRIVER_DEVICE_API_VERSION_0_1;
    // We're forced into this cast by the existing API.  This pattern is
    // common among users of the HAL.
    dev->common.module = const_cast<hw_module_t*>(module);
    dev->common.close = close_rtl8xxxu_driver;
    dev->wifi_driver_initialize = wifi_driver_initialize_rtl8xxxu;
    dev->wifi_driver_set_mode = wifi_driver_set_mode_rtl8xxxu;

    *device = &dev->common;

    return 0;
}

static struct hw_module_methods_t rtl8xxxu_driver_module_methods = {
    .open = open_rtl8xxxu_driver
};

hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = WIFI_DRIVER_HARDWARE_MODULE_ID,
    .name = "rtl8xxxu module",
    .author = "Yudatun",
    .methods = &rtl8xxxu_driver_module_methods,
    .dso = NULL,
    .reserved = {0},
};

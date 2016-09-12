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

static const char *s_rtl8xxxu_modules[] = {
    "/system/lib/modules/rfkill.ko",
    "/system/lib/modules/cfg80211.ko",
    "/system/lib/modules/mac80211.ko",
    "/system/lib/modules/rtl8xxxu.ko",
    NULL,
};

static int insmod(const char *filename, const char *options, int flags)
{
    int fd = open(filename, O_RDONLY | O_NOFOLLOW);
    if (fd == -1) {
        ALOGE("insmod: open '%s' error: %s\n", filename, strerror(errno));
        return -1;
    }
    int rc = syscall(__NR_finit_module, fd, options, flags);
    if (rc == -1) {
        ALOGE("finit_module for '%s' error: %s", filename, strerror(errno));
    }
    close(fd);
    return rc;
}

static wifi_driver_error wifi_driver_initialize_rtl8xxxu(void)
{
    int i = 0;
    int rc;

    for (i = 0; s_rtl8xxxu_modules[i] != NULL; ++i) {
        rc = insmod(s_rtl8xxxu_modules[i], NULL, 0);
    }

    return rc == 0 ? WIFI_SUCCESS : WIFI_ERROR_UNKNOWN;
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

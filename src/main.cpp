/*
 * Copyright (C) 2023 Renesas Electronics Corporation.
 * Copyright (C) 2023 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/__assert.h>
#include <zephyr/sys/printk.h>

#include <aos/common/tools/string.hpp>
#include <aos/common/version.hpp>

#include "app/app.hpp"
#include "logger/logger.hpp"
#include "version.hpp"

#if !defined(CONFIG_NATIVE_APPLICATION)
#include "bsp/mount.h"
#include "bsp/reboot.h"
#include "domains/dom_runner.h"
#endif

#include <psa/crypto.h>

int main(void)
{
    printk("*** Aos zephyr application: %s ***\n", AOS_ZEPHYR_APP_VERSION);
    printk("*** Aos core library: %s ***\n", AOS_CORE_VERSION);
    printk("*** Aos core size: %lu ***\n", sizeof(App));

#if !defined(CONFIG_NATIVE_APPLICATION)
    if (auto ret = littlefs_mount()) {
        printk("Failed to mount littlefs (%d)\n", ret);
    }

    reboot_watcher_init();

    if (auto ret = create_domains()) {
        printk("Failed to create domain (%d)\n", ret);
    }
#endif
#if 0
    Logger::Init();

    auto& app = App::Get();

    auto err = app.Init();
    __ASSERT(err.IsNone(), "Error initializing application: %s", err.Message());
#endif

    psa_status_t status;
    uint8_t      randoms[12];

    status = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        printk("psa_crypto_init() failed: %d", status);
        return 0;
    }

    status = psa_generate_random(randoms, sizeof(randoms));
    if (status == PSA_SUCCESS) {
        printk("Generated random numbers.\n");
    } else {
        printk("Failed to generate random numbers: %d\n", status);
    }

    return 0;
}

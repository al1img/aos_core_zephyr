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

#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/pk.h>
#include <mbedtls/x509_csr.h>

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

    mbedtls_x509write_csr    req;
    mbedtls_entropy_context  entropy;
    mbedtls_ctr_drbg_context ctrDrbg;
    mbedtls_pk_context       pk;

    auto ret = psa_crypto_init();
    if (ret != 0) {
        printk("Error init psa: %d\n", ret);
        return 1;
    }

    mbedtls_pk_init(&pk);

    ret = mbedtls_pk_setup_opaque(&pk, MBEDTLS_PSA_KEY_ID_BUILTIN_MIN);
    if (ret != 0) {
        printk("Error setup opaque: %d\n", ret);
        return 1;
    }

    mbedtls_x509write_csr_init(&req);
    mbedtls_ctr_drbg_init(&ctrDrbg);
    mbedtls_x509write_csr_set_md_alg(&req, MBEDTLS_MD_SHA256);

    mbedtls_x509write_csr_set_key(&req, &pk);

    unsigned char output_buf[4096];

    memset(output_buf, 0, 4096);
    ret = mbedtls_x509write_csr_pem(&req, output_buf, 4096, mbedtls_ctr_drbg_random, &ctrDrbg);
    if (ret != 0) {
        printk("Error create csr: %d\n", ret);
        return 1;
    }

    mbedtls_x509write_csr_free(&req);
    mbedtls_pk_free(&pk);
    mbedtls_ctr_drbg_free(&ctrDrbg);
    mbedtls_entropy_free(&entropy);

    return 0;
}

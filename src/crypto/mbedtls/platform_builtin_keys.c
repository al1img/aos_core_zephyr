/*
 * Copyright (C) 2024 Renesas Electronics Corporation.
 * Copyright (C) 2024 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <psa/crypto.h>
#include <psa/crypto_extra.h>

#if defined(PSA_CRYPTO_DRIVER_AOS)
#include "drivers/aos_driver.h"
#endif

psa_status_t mbedtls_psa_platform_get_builtin_key(
    mbedtls_svc_key_id_t key_id, psa_key_lifetime_t* lifetime, psa_drv_slot_number_t* slot_number)
{
#if defined(PSA_CRYPTO_DRIVER_AOS)

    *lifetime    = PSA_CRYPTO_AOS_DRIVER_LOCATION;
    *slot_number = 0;

    return PSA_SUCCESS;
#else
    return PSA_ERROR_DOES_NOT_EXIST;
#endif
}

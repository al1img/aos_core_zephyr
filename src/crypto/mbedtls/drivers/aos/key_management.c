/*
 * Copyright (C) 2024 Renesas Electronics Corporation.
 * Copyright (C) 2024 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "key_management.h"

psa_status_t mbedtls_aos_opaque_get_builtin_key(psa_drv_slot_number_t slot_number, psa_key_attributes_t* attributes,
    uint8_t* key_buffer, size_t key_buffer_size, size_t* key_buffer_length)
{

    if (key_buffer_size < sizeof(psa_key_id_t)) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    *((psa_key_id_t*)key_buffer) = MBEDTLS_PSA_KEY_ID_BUILTIN_MIN;
    *key_buffer_length           = sizeof(psa_key_id_t);

    return PSA_SUCCESS;
}

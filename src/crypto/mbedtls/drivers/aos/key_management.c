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

    psa_set_key_type(attributes, PSA_KEY_TYPE_RSA_KEY_PAIR);
    psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_SIGN_HASH);

    return PSA_SUCCESS;
}

size_t mbedtls_aos_opaque_size_function(const mbedtls_svc_key_id_t key_id)
{
    return sizeof(psa_key_id_t);
}

psa_status_t mbedtls_aos_opaque_export_public_key(const psa_key_attributes_t* attributes, const uint8_t* key_buffer,
    size_t key_buffer_size, uint8_t* data, size_t data_size, size_t* data_length)
{
    printk("test 0x%X\n", *((psa_key_id_t*)key_buffer));

    return PSA_SUCCESS;
}

/*
 * Copyright (C) 2024 Renesas Electronics Corporation.
 * Copyright (C) 2024 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AOS_KEY_MANAGEMENT_H
#define AOS_KEY_MANAGEMENT_H

#include <psa/crypto.h>

psa_status_t mbedtls_aos_opaque_get_builtin_key(psa_drv_slot_number_t slot_number, psa_key_attributes_t* attributes,
    uint8_t* key_buffer, size_t key_buffer_size, size_t* key_buffer_length);

size_t mbedtls_aos_opaque_size_function(const mbedtls_svc_key_id_t key_id);

psa_status_t mbedtls_aos_opaque_export_public_key(const psa_key_attributes_t* attributes, const uint8_t* key_buffer,
    size_t key_buffer_size, uint8_t* data, size_t data_size, size_t* data_length);

#endif

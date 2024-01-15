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
#endif

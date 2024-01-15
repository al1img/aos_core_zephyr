/*
 * Copyright (C) 2024 Renesas Electronics Corporation.
 * Copyright (C) 2024 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PSA_CRYPTO_AOS_DRIVER_H
#define PSA_CRYPTO_AOS_DRIVER_H

#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif

#define PSA_CRYPTO_AOS_DRIVER_LOCATION 0x800000

#include "aos/key_management.h"

#endif

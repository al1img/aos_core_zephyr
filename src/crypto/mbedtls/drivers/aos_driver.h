/*
 * Copyright (C) 2024 Renesas Electronics Corporation.
 * Copyright (C) 2024 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PSA_CRYPTO_AOS_DRIVER_H
#define PSA_CRYPTO_AOS_DRIVER_H

#if defined(PSA_CRYPTO_DRIVER_AOS)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif

#define PSA_CRYPTO_AOS_DRIVER_LOCATION 0x800000

#endif /* PSA_CRYPTO_DRIVER_AOS */

#endif /* PSA_CRYPTO_AOS_DRIVER_H */

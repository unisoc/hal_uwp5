/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __HAL_SOC_H
#define __HAL_SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uwp_hal.h"

extern void uwp_cache_init(void);
extern void uwp_glb_init(void);
extern int uwp_mcu_init(void);

#ifdef __cplusplus
}
#endif

#endif

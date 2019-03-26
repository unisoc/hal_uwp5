/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file header for uwp pin multiplexing
 */

#ifndef _HAL_PINMUX_UWP5662_H_
#define _HAL_PINMUX_UWP5662_H_

#include "uwp_hal.h"
#include <device.h>

/* pretend that array will cover pin functions */

static inline void __pin_enbable(u8_t enable)
{
	u32_t regval;

	regval  = sys_read32(REG_APB_EB);
	if (enable) {
		sys_write32(regval | BIT_APB_PIN_EB, REG_APB_EB);
	} else {
		sys_write32(regval & (~BIT_APB_PIN_EB), REG_APB_EB);
	}
}

static inline void uwp_pmux_func_clear(u32_t pin_reg)
{
		sci_glb_clr(pin_reg, PIN_FUNC_MSK);
}

static inline void uwp_pmux_func_set(u32_t pin_reg, u32_t func)
{
		if (func & PIN_FUNC_MSK) {
			u32_t conf = sys_read32(pin_reg);

			conf |= func;
			sci_glb_set(pin_reg, conf);
		}
		if (func & (~PIN_FUNC_MSK)) {
			u32_t conf = sys_read32(GROUP(pin_reg));

			conf |= (func & (~PIN_FUNC_MSK));
			sci_glb_set(GROUP(pin_reg), conf);
		}
}

static inline void uwp_pmux_get(u32_t pin_reg, u32_t *func)
{
	u32_t conf = sys_read32(pin_reg);

	*func = conf;
}

static inline void uwp_pmux_pin_pullup(u32_t pin_reg)
{
		u32_t conf = sys_read32(GROUP(pin_reg));

		sci_glb_clr(GROUP(pin_reg), PIN_FPU_MSK);
		conf |= PIN_FPU_EN;
		sci_glb_set(GROUP(pin_reg), conf);
}

static inline void uwp_pmux_pin_pulldown(u32_t pin_reg)
{
		u32_t conf = sys_read32(GROUP(pin_reg));

		sci_glb_clr(GROUP(pin_reg), PIN_FPU_MSK);
		conf |= PIN_FPD_EN;
		sci_glb_set(GROUP(pin_reg), conf);
}

#endif	/* _STM32_PINMUX_H_ */

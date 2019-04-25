/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file header for uwp pin multiplexing
 */

#ifndef _HAL_PINMUX_UWP5661_H_
#define _HAL_PINMUX_UWP5661_H_

#include "uwp_hal.h"
#include <device.h>

#define GPIO_HIGHZ		(1<<31)

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
		u32_t conf = sys_read32(pin_reg);

		conf &= (~PIN_FUNC_MSK);
		sys_write32(conf, pin_reg);
}

static inline void uwp_pmux_func_set(u32_t pin_reg, u32_t func)
{
	u32_t conf = sys_read32(pin_reg);

	func &= (~GPIO_HIGHZ);
	conf |= (~(func|GPIO_HIGHZ));
	sys_write32(conf, pin_reg);

	if (func & GPIO_HIGHZ) {
		conf &= (~(PIN_O_EN|PIN_I_EN));

		conf &= (~(PIN_FPD_EN|PIN_FPU_EN));
	}
	sys_write32(conf, pin_reg);
}

static inline void uwp_pmux_get(u32_t pin_reg, u32_t *func)
{
	u32_t conf = sys_read32(pin_reg);

	*func = conf;
}

static inline void uwp_pmux_pin_pullup(u32_t pin_reg)
{
		u32_t conf = sys_read32(pin_reg);

		conf &= (~PIN_FPU_MSK);
		conf |= PIN_FPU_EN;
		sys_write32(conf, pin_reg);
}

static inline void uwp_pmux_pin_pulldown(u32_t pin_reg)
{
		u32_t conf = sys_read32(pin_reg);

		conf &= (~PIN_FPU_MSK);
		conf |= PIN_FPD_EN;
		sys_write32(conf, pin_reg);
}

#endif	/* _STM32_PINMUX_H_ */

/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __MARLIN3_HAL_SFC_H
#define __MARLIN3_HAL_SFC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/types.h>
#include <arch/arm/cortex_m/exc.h>
#include <irq.h>

#include "uwp_hal.h"

#define DMA_BASE_ADDR		(0x40120000)
#define DMA_UWP_IRQ			25
#define DMA_UWP_IRQ_PROI	3
	
	enum dma_channel_status{
		CHANNEL_IDLE = 0,
		CHANNEL_BUSY,
	};

	enum dma_channel_type{
		TYPE_STANDARD = 0,
		TYPE_FULL,
		TYPE_MAX,
	};

	struct dma_gen_ctl {
		u32_t	dma_pause;
		u32_t	dma_blk_len;
		u32_t	dma_int_raw_status;
		u32_t	dma_int_mask_status;
		u32_t	dma_int_req_status;
		u32_t	dma_en_status;
		u32_t	dma_err_status;
	};

	struct dma_full_chn_cfg {
		u32_t	pause;
		u32_t	req;
		u32_t	cfg;
		u32_t	chn_int;
		u32_t	src_addr;
		u32_t	dest_addr;
		u32_t	frag_len;
		u32_t	blk_len;
		u32_t	trsc_len;
		u32_t	trsf_step;
		u32_t	wrap_ptr;
		u32_t	wrap_to;
		u32_t	llist_ptr;
		u32_t	frag_step;
		u32_t	src_blk_step;
		u32_t	dest_blk_step;
	};

	void dma_enable()
	{
		sci_reg_or(REG_AHB_EB0, BIT(0));
	}

	void dma_rst()
	{
		int i = 0;
		sci_reg_or(REG_AHB_RST0, BIT(0));
		for(i = 0; i < 500; i++);
		sci_reg_and(REG_AHB_RST0, ~BIT(0));
	}

	int check_irq_status(int index) {
		if(sci_read32(DMA_BASE_ADDR + 0x10) & BIT(index)) {
			printk("channel %d receive irq\n", index);
			sci_reg_and(DMA_BASE_ADDR + 0x10, ~BIT(index));
			return 1;
		} else {
			return 0;
		}
		

	}

	void dma_set_src_addr(u32_t addr, u32_t src)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->src_addr = src;
	}

	void dma_set_dest_addr(u32_t addr, u32_t dest)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->dest_addr = dest;
	}

	void dma_set_blk_len(u32_t addr, u32_t len)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->blk_len = len;
	}
	void dma_set_fix_cfg(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->src_blk_step = 1;
		cfg->dest_blk_step = 1;
		return;
	}
#ifdef __cplusplus
}
#endif

#endif

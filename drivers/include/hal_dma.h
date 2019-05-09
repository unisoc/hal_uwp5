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
#define DMA_MAX_CHANNEL		(32)
#define UART1_DMA_MODE_BASE	(0x40040000 + 0x001C)
#define DMA_CID_ADDR(x)		(DMA_BASE_ADDR + 0x2000 + x*0x4)
/*for clear irq*/
#define CHN_CFG_ERR_CLR		BIT(28)
#define CHN_LLIST_INT_CLR	BIT(27)
#define CHN_TRSC_INT_CLR	BIT(26)
#define CHN_BLK_INT_CLR		BIT(25)
#define CHN_FRAG_INT_CLR	BIT(24)
#define CHN_TRANS_INT		BIT(2)
#define UART_DMA_MODE		BIT(15)
#define DMA_UART1_CID		2
#define DMA_CHANNEL_UART1_TX	0
#define DMA_CHANNEL_UART1_RX	1
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
	
	void reset_channel_cfg(u32_t addr)
	{
		memset(addr, 0, 0x40);
	}
	
	void dma_stop_channel(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->pause = 1;
	}

	void dma_uart_set_len(u32_t addr, u32_t len)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		u32_t min, max = 0, watermark = 64;

		if (len < watermark) {
		    min = len;
		    max = watermark;
		} else {
		    min = watermark;
		    max = len;
		}
		cfg->frag_len = min;
		cfg->blk_len = max;
		cfg->trsc_len = max;
	}

	void dma_set_uart_write_cfg(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->chn_int |= CHN_TRANS_INT;
		cfg->src_blk_step = 1;
		cfg->dest_blk_step = 0;
		return;
	}

	void dma_set_uart_read_cfg(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->src_blk_step = 0;
		cfg->dest_blk_step = 1;
		return;
	}

	void set_channel_enable(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->cfg |= 1;
		return;
	}

	void dma_req_for_uart(u32_t channel)
	{
		sci_write32(DMA_CID_ADDR(DMA_UART1_CID), channel + 1);
	}

	void set_uart_dma_mode(u32_t channel)
	{
		if (channel == DMA_CHANNEL_UART1_TX || channel == DMA_CHANNEL_UART1_RX) {
			sci_reg_or(UART1_DMA_MODE_BASE, UART_DMA_MODE);
		}
	}

	void clear_channel_irq(u32_t addr)
	{
		volatile struct dma_full_chn_cfg* cfg = (struct dma_full_chn_cfg*)addr;
		cfg->chn_int |= (CHN_CFG_ERR_CLR | CHN_LLIST_INT_CLR |
				 CHN_TRSC_INT_CLR | CHN_BLK_INT_CLR | CHN_FRAG_INT_CLR);
	}
#ifdef __cplusplus
}
#endif

#endif

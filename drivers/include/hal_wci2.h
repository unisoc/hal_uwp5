/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __HAL_WCI2_H
#define __HAL_WCI2_H

#ifdef __cplusplus
extern "C" {
#endif

#define MODE_WCI2	0
#define MODE_IRDA	1

#define WCI2_OFFSET_REALTIME_EN	0x0084
#define BIT_WCI2_REALTIME	BIT(0)

#define WCI2_MAX_TX_COUNT 0x1F
	enum {
		WCI2_RXF_FULL = 0,
		WCI2_TXF_EMPTY,
		WCI2_PARITY_ERR,
		WCI2_FRAME_ERR,
		WCI2_RXF_OVERRUN,
		WCI2_DSR_CHG,
		WCI2_CTS_CHG,
		WCI2_BRK_DTCT,
		WCI2_DSR,
		WCI2_CTS,
		WCI2_RTS,
		WCI2_RXD,
		WCI2_RXF_REALEMPTY,
		WCI2_TIME_OUT,
		WCI2_RXF_REALFULL,
		WCI2_TRANS_OVER,
		WCI2_RX_OVER,
		WCI2_TX_OVER,
	};

	typedef struct wci2_txd {
		u32_t txd	:8;
		u32_t rsvd	:24;
	}wci2_txd_t;

	typedef struct wci2_rxd {
		u32_t rxd	:8;
		u32_t rx_timing	:24;
	}wci2_rxd_t;

	typedef struct wci2_sts1 {
		u32_t rxf_cnt		:6;
		u32_t rsvd0		:2;
		u32_t txf_cnt		:6;
		u32_t rsvd1		:18;
	}wci2_sts1_t;

	typedef union wci2_ctrl0 {
		u32_t reg;

		struct {
			u32_t odd_parity	:1;
			u32_t parity_en		:1;
			u32_t byte_len		:2;
			u32_t stop_bit_num	:2;
			u32_t rts_reg		:1;
			u32_t send_brk_en	:1;
			u32_t dtr_reg		:1;
			u32_t ir_tx_iv		:1;
			u32_t ir_rx_iv		:1;
			u32_t ir_tx_en		:1;
			u32_t ir_dplx		:1;
			u32_t ir_wctl		:1;
			u32_t rsvd0		:1;
			u32_t mode_sel		:1;
			u32_t rsvd1		:16;
		}bit;
	}wci2_ctrl0_t;

	typedef union wci2_ctrl1 {
		u32_t reg;

		struct {
			u32_t rcv_hw_flow_thld	:5;
			u32_t rsvd0		:2;
			u32_t rcv_hw_flow_en	:1;
			u32_t tx_hw_flow_en	:1;
			u32_t rx_tout_thld	:5;
			u32_t loop_back		:1;
			u32_t dma_en		:1;
			u32_t rsvd1		:16;
		}bit;
	}wci2_ctrl1_t;

	typedef union wci2_ctrl2 {
		u32_t reg;
		struct {
			u32_t rxf_full_thld	:5;
			u32_t rsvd0		:3;
			u32_t txf_empty_thld	:5;
			u32_t rsvd1		:19;
		}bit;
	}wci2_ctrl2_t;

	typedef struct wci2_cdk0 {
		u32_t cdk0		:16;
		u32_t rsvd		:16;
	}wci2_cdk0_t;

	typedef struct wci2_dspwait {
		u32_t dspwait		:4;
		u32_t rx_dma_mod_sel	:1;
		u32_t tx_dma_mod_sel	:1;
	}wci2_dspwait_t;

	struct uwp_wci2 {
		wci2_txd_t		txd;
		wci2_rxd_t		rxd;
		u32_t			sts0;
		wci2_sts1_t		sts1;
		u32_t			ien;
		u32_t			iclr;
		wci2_ctrl0_t		ctrl0;
		wci2_ctrl1_t		ctrl1;
		wci2_ctrl2_t		ctrl2;
		wci2_cdk0_t		cdk0;
		u32_t	    		sts2;
		wci2_dspwait_t		dspwait;
	};

static inline u32_t uwp_wci2_rx_ready(volatile struct uwp_wci2 *wci2)
{
	return (wci2->sts0 >> WCI2_RXF_FULL) & 0x1;
	//return ((wci2->sts1.rxf_cnt & 0x1f) > 0) ? 1 : 0;
}

static inline u32_t uwp_wci2_tx_ready(volatile struct uwp_wci2 *wci2)
{
	return (wci2->sts0 >> WCI2_TXF_EMPTY) & 0x1;
}

static inline u8_t uwp_wci2_read(volatile struct uwp_wci2 *wci2)
{
	return wci2->rxd.rxd;
}

static inline void uwp_wci2_write(volatile struct uwp_wci2 *wci2,
		u8_t c)
{
	wci2->txd.txd = c;
}

static inline u32_t uwp_wci2_trans_over(volatile struct uwp_wci2 *wci2)
{
	return wci2->sts0 & BIT(WCI2_TRANS_OVER);
}

static inline void uwp_wci2_set_cdk(volatile struct uwp_wci2 *wci2,
		u32_t cdk)
{
	wci2->cdk0.cdk0 = cdk;
}

static inline void uwp_wci2_set_stop_bit_num(volatile struct uwp_wci2 *wci2,
		u32_t stop_bit_num)
{
	wci2->ctrl0.bit.stop_bit_num = stop_bit_num;
}

static inline void uwp_wci2_set_byte_len(volatile struct uwp_wci2 *wci2,
		u32_t byte_len)
{
	wci2->ctrl0.bit.byte_len = byte_len;
}

static inline void uwp_wci2_init(volatile struct uwp_wci2 *wci2)
{
//	wci2->cdk0.cdk0 = 0xe1;

	wci2->ien = 0;
	wci2->ctrl1.bit.rx_tout_thld = 1;
	wci2->ctrl2.bit.rxf_full_thld = 1;
	wci2->ctrl2.bit.txf_empty_thld = 16;
}

static inline void uwp_wci2_int_enable(volatile struct uwp_wci2 *wci2,
		u32_t flags)
{
	wci2->ien |= flags;
}

static inline void uwp_wci2_int_disable(volatile struct uwp_wci2 *wci2,
		u32_t flags)
{
	wci2->ien &= ~flags;
}

static inline void uwp_wci2_int_clear(volatile struct uwp_wci2 *wci2,
		u32_t flags)
{
	wci2->iclr |= flags;
}

static inline u32_t uwp_wci2_status(volatile struct uwp_wci2 *wci2)
{
	return wci2->sts0;
}

static inline void uwp_wci2_set_mode(u32_t base_addr)
{
	u32_t realtime_en = base_addr + WCI2_OFFSET_REALTIME_EN;

	sci_reg_and(realtime_en, ~BIT_WCI2_REALTIME);
}
#ifdef __cplusplus
}
#endif

#endif

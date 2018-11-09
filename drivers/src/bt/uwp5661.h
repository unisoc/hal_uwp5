/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BT_UWP5661_H_
#define __BT_UWP5661_H_

#include <stdint.h>

#define BT_HCI_OP_PSKEY 0xFCA0
#define BT_HCI_OP_RF 0xFCA2
#define BT_HCI_OP_ENABLE_CMD 0xFCA1

#define HCI_CMD_MAX_LEN 258
#define HCI_CMD_PREAMBLE_SIZE 3

void uwp5661_vendor_init(void);

#endif

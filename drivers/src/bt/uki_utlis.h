/*
 * Copyright (c) 2018, UNISOC Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BT_UKI_UTLIS_H_
#define __BT_UKI_UTLIS_H_

#define HEX_DUMP_BLOCK_SIZE 20

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4
#define LOG_LEVEL_VERBOSE 5

extern int vendor_log_level;
extern int stack_log_level;

static inline void set_vendor_log_level(int level) {
	vendor_log_level = level;
	printk("%s: %d\n",__func__, vendor_log_level);
}

static inline void set_stack_log_level(int level) {
	stack_log_level = level;
	printk("%s: %d\n",__func__, stack_log_level);
}


#define BTE(fmt, ...) 							\
	do { 										\
		if (vendor_log_level >= LOG_LEVEL_ERROR) { 	\
			printk(fmt, ##__VA_ARGS__); 		\
		} 										\
	}while(0)


#define BTW(fmt, ...) 							\
	do {										\
		if (vendor_log_level >= LOG_LEVEL_WARNING) { 	\
			printk(fmt, ##__VA_ARGS__); 		\
		}										\
	}while(0)

#define BTI(fmt, ...) 							\
	do {										\
		if (vendor_log_level >= LOG_LEVEL_INFO) {		\
			printk(fmt, ##__VA_ARGS__); 		\
		}										\
	}while(0)

#define BTD(fmt, ...) 							\
	do {										\
		if (vendor_log_level >= LOG_LEVEL_DEBUG) {		\
			printk(fmt, ##__VA_ARGS__); 		\
		}										\
	}while(0)

#define BTV(fmt, ...) 							\
	do {										\
		if (vendor_log_level >= LOG_LEVEL_VERBOSE) { 	\
			printk(fmt, ##__VA_ARGS__); 		\
		}										\
	}while(0)


void uki_hex_dump_block(char *tag, unsigned char *bin, size_t binsz);
void uki_hex(char *dst, unsigned char *src, size_t binsz);

#define HCIDUMP(tag, bin, binsz) 					\
	do {											\
		if (vendor_log_level >= LOG_LEVEL_DEBUG) { 		\
			uki_hex_dump_block(tag, bin, binsz); 	\
		}											\
	}while(0)

#endif  // LIBBT_CONF_SPRD_MARLIN_INCLUDE_MARLIN_H_
/*
 * gdt.h - Header file for GDT.
 *
 * Author: Philip R. Simonson
 * Date: 12/25/2020
 *
 **********************************************************************
 */

#ifndef _GDT_H_
#define _GDT_H_

#include "types.h"

#define MAX_GDT_ENTRIES 5

struct gdt_entry {
	u16_t limit;
	u16_t base_low;
	u8_t base_mid;
	u8_t access;
	u8_t grand;
	u8_t base_high;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

/* Reload GDT into system. */
extern void gdt_flush(u32_t gdtr);

/* Install new GDT into system. */
extern void gdt_install(void);

#endif

/*
 * gdt.h - Header file for Global Descriptor Table (GDT).
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 *********************************************************************
 */

#ifndef _GDT_H_
#define _GDT_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Max descriptors allowed.
#define MAX_DESCRIPTORS			3

// GDT Descriptor access bit flags.
#define I86_GDT_DESC_ACCESS					0X0001
#define I86_GDT_DESC_READWRITE			0X0002
#define I86_GDT_DESC_EXPANSION			0x0004
#define I86_GDT_DESC_EXEC_CODE			0x0008
#define I86_GDT_DESC_CODEDATA				0x0010
#define I86_GDT_DESC_DPL						0x0060
#define I86_GDT_DESC_MEMORY					0x0080

// GDT Descriptor grandularity bit flags.
#define I86_GDT_GRAND_LIMITHI_MASK	0x0F
#define I86_GDT_GRAND_OS						0x10
#define I86_GDT_GRAND_32BIT					0x40
#define I86_GDT_GRAND_4K						0x80

// GDT Descriptor.
struct gdt_descriptor {
	u16_t limit;
	u16_t base_low;
	u8_t base_mid;
	u8_t flags;
	u8_t grand;
	u8_t base_high;
} __attribute__((packed));

/* Setup a descriptor in the GDT. */
extern void gdt_set_descriptor(u32_t i, u64_t base, u64_t limit, u8_t access,
	u8_t grand);
/* Return a descriptor. */
extern gdt_descriptor *i86_gdt_get_descriptor(int i);
/* Initialize the GDT. */
extern void i86_gdt_init(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 * idt.h - Header file for IDT implementation (data types and defines).
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 ***********************************************************************
 */

#ifndef _IDT_H_
#define _IDT_H_

#include "types.h"

/* Segment selectors. */
#define KERNEL_CS 0x08

/* Interrupt gate handler definition. */
typedef struct idt_gate {
	u16_t low_offset;
	u16_t sel;
	u8_t always0;
	u8_t flags;
	u16_t high_offset;
} __attribute__((packed)) idt_gate_t;

/* A point to the array of interrupt handlers. */
typedef struct idt_reg {
	u16_t limit;
	u32_t base;
} __attribute__((packed)) idt_reg_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_reg_t idt_reg;

/* Functions implemented in idt.c. */
extern void set_idt_gate(int n, u32_t handler);
extern void set_idt(void);

#endif

/*
 * idt.c - Source file for the IDT implementation.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 **************************************************************
 */

#include "idt.h"
#include "util.h"
#include "vga.h"

static idt_gate_t idt[IDT_ENTRIES];
static idt_reg_t idt_reg;

/* Set the IDT handlers one at a time.
 */
void set_idt_gate(int n, u32_t handler)
{
	idt[n].low_offset = low_16(handler);
	idt[n].sel = KERNEL_CS;
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler);
}
/* Loads the IDT into system.
 */
void set_idt(void)
{
	idt_reg.base = (u32_t)&idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
	__asm__ __volatile__("lidtl (%0)" : : "r"(&idt_reg));
}

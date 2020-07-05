/*
 * isr.c - Source file for the ISR implementation.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 ***************************************************************
 */

#include "isr.h"
#include "idt.h"
#include "vga.h"
#include "util.h"
#include "helper.h"
#include "io.h"
#include "ports.h"
#include "keyboard.h"

isr_t interrupt_handlers[256];

/* Exception messages to print. */
char *exception_messages[32] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/* Map interrupts to the service routines.
 */
void isr_install(void)
{
	/* Install ISRs */
	set_idt_gate(0, (u32_t)isr0);
	set_idt_gate(1, (u32_t)isr1);
	set_idt_gate(2, (u32_t)isr2);
	set_idt_gate(3, (u32_t)isr3);
	set_idt_gate(4, (u32_t)isr4);
	set_idt_gate(5, (u32_t)isr5);
	set_idt_gate(6, (u32_t)isr6);
	set_idt_gate(7, (u32_t)isr7);
	set_idt_gate(8, (u32_t)isr8);
	set_idt_gate(9, (u32_t)isr9);
	set_idt_gate(10, (u32_t)isr10);
	set_idt_gate(11, (u32_t)isr11);
	set_idt_gate(12, (u32_t)isr12);
	set_idt_gate(13, (u32_t)isr13);
	set_idt_gate(14, (u32_t)isr14);
	set_idt_gate(15, (u32_t)isr15);
	set_idt_gate(16, (u32_t)isr16);
	set_idt_gate(17, (u32_t)isr17);
	set_idt_gate(18, (u32_t)isr18);
	set_idt_gate(19, (u32_t)isr19);
	set_idt_gate(20, (u32_t)isr20);
	set_idt_gate(21, (u32_t)isr21);
	set_idt_gate(22, (u32_t)isr22);
	set_idt_gate(23, (u32_t)isr23);
	set_idt_gate(24, (u32_t)isr24);
	set_idt_gate(25, (u32_t)isr25);
	set_idt_gate(26, (u32_t)isr26);
	set_idt_gate(27, (u32_t)isr27);
	set_idt_gate(28, (u32_t)isr28);
	set_idt_gate(29, (u32_t)isr29);
	set_idt_gate(30, (u32_t)isr30);
	set_idt_gate(31, (u32_t)isr31);
	/* Remap the PIC */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);
	/* Install IRQs */
	set_idt_gate(32, (u32_t)irq0);
	set_idt_gate(32, (u32_t)irq1);
	set_idt_gate(32, (u32_t)irq2);
	set_idt_gate(32, (u32_t)irq3);
	set_idt_gate(32, (u32_t)irq4);
	set_idt_gate(32, (u32_t)irq5);
	set_idt_gate(32, (u32_t)irq6);
	set_idt_gate(32, (u32_t)irq7);
	set_idt_gate(32, (u32_t)irq8);
	set_idt_gate(32, (u32_t)irq9);
	set_idt_gate(32, (u32_t)irq10);
	set_idt_gate(32, (u32_t)irq11);
	set_idt_gate(32, (u32_t)irq12);
	set_idt_gate(32, (u32_t)irq13);
	set_idt_gate(32, (u32_t)irq14);
	set_idt_gate(32, (u32_t)irq15);
	/* Load IDT with assembly */
	set_idt();
}
/* Generic exception handler.
 */
void isr_handler(registers_t *r)
{
	print("Received interrupt: ");
	char s[4];
	itoa(r->int_no, s);
	print(s);
	print("Raised Exception: ");
	print(exception_messages[r->int_no]);
	print("\n");
}
/* Register interrupt handler.
 */
void register_interrupt_handler(u8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}
/* Handle IRQs.
 */
void irq_handler(registers_t *r)
{
	if(r->int_no >= 40) outb(0xA0, 0x20); // slave
	else outb(0x20, 0x20); // master

	/* Handle the interrupt in a modular way */
	if(interrupt_handlers[r->int_no] != 0) {
		isr_t handler = interrupt_handlers[r->int_no];
		handler(r);
	}
}
/* Install the IRQs.
 */
void irq_install(void)
{
	/* Enable interruptions */
	__asm__ __volatile__("sti");
	/* IRQ0: timer */
//	init_timer(50);
	/* IRQ1: keyboard */
	init_keyboard();
}

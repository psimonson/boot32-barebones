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
#include "pit.h"
#include "system.h"

isr_t interrupt_handlers[256];

/* Exception messages to print. */
static char *exception_messages[32] = {
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
	disable();
	/* Install ISRs */
	SET_ISR(0);
	SET_ISR(1);
	SET_ISR(2);
	SET_ISR(3);
	SET_ISR(4);
	SET_ISR(5);
	SET_ISR(6);
	SET_ISR(7);
	SET_ISR(8);
	SET_ISR(9);
	SET_ISR(10);
	SET_ISR(11);
	SET_ISR(12);
	SET_ISR(13);
	SET_ISR(14);
	SET_ISR(15);
	SET_ISR(16);
	SET_ISR(17);
	SET_ISR(18);
	SET_ISR(19);
	SET_ISR(20);
	SET_ISR(21);
	SET_ISR(22);
	SET_ISR(23);
	SET_ISR(24);
	SET_ISR(25);
	SET_ISR(26);
	SET_ISR(27);
	SET_ISR(28);
	SET_ISR(29);
	SET_ISR(30);
	SET_ISR(31);
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
	SET_IRQ(0);
	SET_IRQ(1);
	SET_IRQ(2);
	SET_IRQ(3);
	SET_IRQ(4);
	SET_IRQ(5);
	SET_IRQ(6);
	SET_IRQ(7);
	SET_IRQ(8);
	SET_IRQ(9);
	SET_IRQ(10);
	SET_IRQ(11);
	SET_IRQ(12);
	SET_IRQ(13);
	SET_IRQ(14);
	SET_IRQ(15);
	/* Load IDT with assembly */
	set_idt();
	enable();
}
/* Generic exception handler.
 */
void isr_handler(registers_t *r)
{
	clear_screen();
	kprintf("Received interrupt: %d\n"
		"Raised Exception: %s\n", r->int_no, exception_messages[r->int_no]);
	halt();
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
	/* Handle the interrupt in a modular way */
	if(interrupt_handlers[r->int_no] != 0) {
		isr_t handler = interrupt_handlers[r->int_no];
		handler(r);
	}

	if(r->int_no >= 40) outb(0xA0, 0x20); // slave
	outb(0x20, 0x20); // master
}
/* Install the IRQs.
 */
void irq_install(void)
{
	/* IRQ0: timer */
	install_timer(50);
	/* IRQ1: keyboard */
	install_kbd();
}

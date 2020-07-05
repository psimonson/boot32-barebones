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
#include "timer.h"

isr_t interrupt_handlers[256];

/* Map interrupts to the service routines.
 */
void isr_install(void)
{
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
	SET_IRQ(32, 0);
	SET_IRQ(33, 1);
	SET_IRQ(34, 2);
	SET_IRQ(35, 3);
	SET_IRQ(36, 4);
	SET_IRQ(37, 5);
	SET_IRQ(38, 6);
	SET_IRQ(39, 7);
	SET_IRQ(40, 8);
	SET_IRQ(41, 9);
	SET_IRQ(42, 10);
	SET_IRQ(43, 11);
	SET_IRQ(44, 12);
	SET_IRQ(45, 13);
	SET_IRQ(46, 14);
	SET_IRQ(47, 15);
	/* Load IDT with assembly */
	set_idt();
}

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

/* Generic exception handler.
 */
void isr_handler(registers_t *r)
{
	char s[5];
	print("Received interrupt: ");
	itoa(r->int_no, s);
	print(s);
	print("\n");
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
	outb(0x20, 0x20); // master

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
	install_timer(50);
	/* IRQ1: keyboard */
	install_keyboard();
}

#define DEF_ISR(X) void isr##X(registers_t *r)
#define DEF_IRQ(X) void irq##X(registers_t *r)

/* ---------------------------- ISRs Below ---------------------------- */

DEF_ISR(0) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(1) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(2) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(3) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(4) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(5) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(6) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(7) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(8) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(9) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(10) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(11) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(12) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(13) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(14) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(15) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(16) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(17) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(18) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(19) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(20) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(21) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(22) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(23) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(24) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(25) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(26) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(27) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(28) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(29) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(30) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}
DEF_ISR(31) {
	isr_handler(r);
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
}

/* ---------------------------- IRQs Below ---------------------------- */

DEF_IRQ(0) {
	irq_handler(r);
}
DEF_IRQ(1) {
	irq_handler(r);
}
DEF_IRQ(2) {
	irq_handler(r);
}
DEF_IRQ(3) {
	irq_handler(r);
}
DEF_IRQ(4) {
	irq_handler(r);
}
DEF_IRQ(5) {
	irq_handler(r);
}
DEF_IRQ(6) {
	irq_handler(r);
}
DEF_IRQ(7) {
	irq_handler(r);
}
DEF_IRQ(8) {
	irq_handler(r);
}
DEF_IRQ(9) {
	irq_handler(r);
}
DEF_IRQ(10) {
	irq_handler(r);
}
DEF_IRQ(11) {
	irq_handler(r);
}
DEF_IRQ(12) {
	irq_handler(r);
}
DEF_IRQ(13) {
	irq_handler(r);
}
DEF_IRQ(14) {
	irq_handler(r);
}
DEF_IRQ(15) {
	irq_handler(r);
}

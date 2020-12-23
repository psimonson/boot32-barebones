/*
 * hal.c - Hardware Abstraction Layer (HAL) interface source file.
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 *********************************************************************
 */

#include "hal.h"
#include "cpu.h"
#include "idt.h"
#include "pit.h"
#include "pic.h"
#include "vga.h"
#include "system.h"
#include "keyboard.h"

/* Initialize HAL interface.
 */
void hal_init(void)
{
	disable();
	i86_cpu_init();
	i86_pic_init(0x20, 0x28);
	i86_pit_init();
	i86_pit_start_counter(100, I86_PIT_OCW_COUNTER_0,
		I86_PIT_OCW_MODE_SQUAREWAVEGEN);
	install_kbd();

	enable(); // Restore interrupts
}
/* Shutdown HAL interface.
 */
void hal_shutdown(void)
{
	i86_cpu_shutdown();
}
/* Tell HAL that an interrupt is done.
 */
void interrupt_done(unsigned int intno)
{
	// Insure its a valid hardware IRQ.
	if(intno >= 256) return;

	// Test if end-of-interrupt to second PIC.
	if(intno >= 40)
		i86_pic_send_command(I86_PIC_OCW2_MASK_EOI, 1);

	// Always send end-of-interrupt to primary PIC.
	i86_pic_send_command(I86_PIC_OCW2_MASK_EOI, 0);
}
/* Set new interrupt vector.
 */
void set_vect(int intno, void (*vect)())
{
	register_interrupt_handler(intno, vect);
}
/* Get current interrupt vector.
 */
isr_handler_t get_vect(int intno)
{
	// Get the descriptor from the idt.
	struct idt_gate *desc = 0; //i86_get_ir(intno);
	if(!desc) return 0;

	// Get address of interrupt handler.
	u32_t addr = desc->low_offset | (desc->high_offset << 16);

	// Return interrupt handler.
	isr_handler_t irq = (isr_handler_t)addr;
	return irq;
}

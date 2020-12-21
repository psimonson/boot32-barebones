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
#include "system.h"

/* Initialize HAL interface.
 */
void hal_init(void)
{
	i86_cpu_init();
	i86_pic_init(0x20, 0x28);
	i86_pit_init();
	i86_pit_start_counter(100, I86_PIT_OCW_COUNTER_0,
		I86_PIT_OCW_MODE_SQUAREWAVEGEN);

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
inline void interrupt_done(unsigned int intno)
{
	// Insure its a valid hardware IRQ.
	if(intno > 16) return;

	// Test if end-of-interrupt to second PIC.
	if(intno >= 8)
		i86_pic_send_command(0xA0, 1);

	// Always send end-of-interrupt to primary PIC.
	i86_pic_send_command(0x20, 0);
}
/* Set new interrupt vector.
 */
void set_vect(int intno, void (*vect)())
{
	i86_install_ir(intno, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32,
		0x8, vect);
}
/* Get current interrupt vector.
 */
void (*get_vect(int intno))()
{
	// Get the descriptor from the idt.
	idt_descriptor *desc = i86_get_ir(intno);
	if(!desc) return 0;

	// Get address of interrupt handler.
	addr = desc->base_low | (desc->base_high << 16);

	// Return interrupt handler.
	I86_IRQ_HANDLER irq = (I86_IRQ_HANDLER)addr;
	return addr;
}
